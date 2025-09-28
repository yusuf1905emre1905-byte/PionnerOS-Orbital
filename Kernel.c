// =========================================================
// PionnerOS - Orbital Çekirdeği (MASTER VİZYON SÜRÜMÜ)
// Kapsanan Vizyonlar: VGA Renk, Klavye Haritası, Kopyala/Yapıştır, Pionner HUB Uygulama Mağazası
// =========================================================

// =========================================================
// BÖLÜM 1: DÜŞÜK SEVİYE DONANIM ERİŞİMLERİ (I/O Portları)
// =========================================================

// Porttan bir bayt (8 bit) okur
unsigned char inb(unsigned short port) {
    unsigned char result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

// Porta bir bayt (8 bit) yazar
void outb(unsigned short port, unsigned char data) {
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}


// =========================================================
// BÖLÜM 2: KONSOL (VGA) VE TEMEL ÇIKTI YÖNETİMİ
// =========================================================

volatile unsigned short *vga_buffer = (unsigned short *)0xB8000;
int cursor_x = 0;
int cursor_y = 0;
unsigned char terminal_color = 0x1F; // Mavi Arka Plan (1), Parlak Beyaz Yazı (F)

// Komut Satırı ve Kopyala/Yapıştır için Global Tanımlamalar
#define COMMAND_MAX_LENGTH 64
char command_buffer[COMMAND_MAX_LENGTH];
int command_index = 0;

#define CLIPBOARD_MAX_LENGTH 256
char clipboard_buffer[CLIPBOARD_MAX_LENGTH]; // Kopyalanan metin buraya kaydedilir


// Yeni Karakteri Ekrana Yazan Fonksiyon
void putc(char c) {
    unsigned short *location;

    if (c == '\n') {
        cursor_y++;
        cursor_x = 0;
        return;
    }

    location = vga_buffer + (cursor_y * 80 + cursor_x);
    *location = c | (terminal_color << 8);

    cursor_x++;
    
    if (cursor_x >= 80) {
        cursor_x = 0;
        cursor_y++;
    }
}

// Ekrana String (Metin) Yazan Fonksiyon
void puts(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        putc(str[i]);
    }
}

// Ekranı Temizleyen Fonksiyon
void clear_screen() {
    for (int y = 0; y < 25; y++) {
        for (int x = 0; x < 80; x++) {
            vga_buffer[y * 80 + x] = ' ' | (terminal_color << 8);
        }
    }
    cursor_x = 0;
    cursor_y = 0;
}


// =========================================================
// BÖLÜM 3: PIONNER HUB UYGULAMA MAĞAZASI VİZYONU
// =========================================================

// Uygulama Paketi (PPK) Formatı Vizyonu
typedef struct {
    char name[32];        
    char version[16];     
    char description[64]; 
    int is_installed;     
} ppk_package;

// Pionner Hub Uygulama Mağazası Envanteri (Oyunlar Dahil)
ppk_package app_store_inventory[] = {
    {"AYARLAR", "v1.0", "Tum sistemi ayarlama ve uygulama yoneticisi.", 1},
    {"CALENDAR", "v1.0", "RTC ile senkronize calisan takvim uygulamasi.", 0},
    {"PPK_BROWSER", "v0.9", "Sahte sitelerden .ppk indirme vizyonu.", 0},
    {"CALCULATOR", "v2.0", "Gelistirilmis matematiksel islem vizyonu.", 1},
    {"GAME_HUB", "v1.0", "Tum oyunlarin listelendigi uygulama merkezi.", 1},
    {"SNAKE", "v0.1", "Klasik Yilan oyunu vizyonu.", 0},
    {"TETRIS", "v0.1", "Blok yerlestirme oyunu vizyonu.", 0}
};

const int total_apps = sizeof(app_store_inventory) / sizeof(ppk_package);


// Mağaza Arayüzü Vizyonu Fonksiyonu
void show_app_store() {
    puts("\n--- PIONNER HUB UYGULAMA MAGAZASI VIZYONU ---\n");
    puts("Uygulama Adi       | Durum\n");
    puts("--------------------------------------------\n");

    for (int i = 0; i < total_apps; i++) {
        puts(app_store_inventory[i].name);
        
        // Tab boşluğunu simüle etme
        for (int j = 0; j < (18 - (int)sizeof(app_store_inventory[i].name)); j++) {
            puts(" ");
        }
        
        puts("| [");
        puts(app_store_inventory[i].is_installed ? "KURULU" : "INDIILEBILIR");
        puts("]\n");
    }
    puts("--------------------------------------------\n");
}


// =========================================================
// BÖLÜM 4: PS/2 KLAVYE VİZYONU (Kopayla/Yapıştır Dahil)
// =========================================================

// Klavye Kontrolcü (Ctrl tuşu takibi)
int ctrl_pressed = 0; 

// Klavye Haritası: Harf ve sayıların Scancode karşılıkları
const unsigned char keyboard_map[128] =
{
    0,  0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0,  0,
  'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']',  0,  0, 'a', 's',
  'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',  0, '\\', 'z', 'x', 'c', 'v',
  'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0,  0,  0,  0,  0,  0,
    // ...
};

// Gelen Scancode'u Karakter'e Çeviren Fonksiyon
unsigned char scancode_to_char(unsigned char scancode) {
    if (scancode & 0x80) return 0; // Tuş bırakıldıysa görmezden gel
    if (scancode < 128) return keyboard_map[scancode];
    return 0;
}

// Klavye Girişini Yöneten Ana Vizyon Fonksiyonu
void handle_keyboard_input() {
    unsigned char scancode = inb(0x60); 
    
    // BREAK CODE: Tuş Bırakıldı (Ctrl serbest bırakma)
    if (scancode & 0x80) {
        if ((scancode & 0x7F) == 0x1D) ctrl_pressed = 0;
        return; 
    }

    // MAKE CODE: Tuşa Basıldı (Ctrl basma)
    if (scancode == 0x1D) { // Sol Ctrl'ye basıldı
        ctrl_pressed = 1;
        return; 
    }
    
    unsigned char character = scancode_to_char(scancode);

    // CTRL+C (Kopyala Vizyonu)
    if (ctrl_pressed && (character == 'c' || character == 'C')) {
        puts("\n[Kopyalandi: Simule edildi]");
        // Gerçek kopyalama mantığı buraya gelir.
        return;
    }

    // CTRL+V (Yapıştır Vizyonu)
    if (ctrl_pressed && (character == 'v' || character == 'V')) {
        puts("[Yapiştirildi: Simule edildi]");
        // Gerçek yapıştırma mantığı buraya gelir.
        return;
    }
    
    // ENTER Tuşu Mantığı
    if (scancode == 0x1C) {
        puts("\n");
        puts("Komut alindi: [");
        puts(command_buffer);
        puts("] - Calistiriliyor...\n");
        
        // Buffer'ı temizle
        for (int i = 0; i < COMMAND_MAX_LENGTH; i++) command_buffer[i] = 0;
        command_index = 0;
        return;
    }

    // Normal Harf Mantığı
    if (character != 0 && command_index < COMMAND_MAX_LENGTH - 1) {
        putc(character); 
        command_buffer[command_index] = character;
        command_index++;
    }
}


// =========================================================
// BÖLÜM 5: RTC VİZYONU VE GİRİŞ NOKTASI
// =========================================================

// RTC Vizyonu
void read_and_display_time() {
    puts("RTC VIZYONU: [00:00:00 - 01/01/2025] (Zaman Okuma Servisi Aktif)\n");
}


// Çekirdek Giriş Noktası (Kernel Entry Point)
void kernel_main() {
    clear_screen();

    puts("--------------------------------------------------------------------------------\n");
    puts(">> PionnerOS - Orbital [MASTER VIZYON SÜRÜMÜ] - Çekirdek Başlatılıyor...\n");
    puts("--------------------------------------------------------------------------------\n\n");
    
    // Vizyonları Çalıştır
    read_and_display_time(); 
    puts("RTC servisi aktif edildi.\n");

    // PIONNER HUB UYGULAMA MAĞAZASINI AÇ!
    show_app_store(); 
    
    puts("\n[Pionner HUB]: Klavye girisi bekleniyor (Ctrl+C, Ctrl+V destekli).\n");
    
    // Sonsuz döngü
    while (1) {
        handle_keyboard_input(); 
    }
}
