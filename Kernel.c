// kernel.c - PionnerOS Orbital Çekirdeği (NİHAİ VE SON VERSİYON)

// --- TANIMLAMALAR ---
#define COLOR_WHITE 0xFFFFFF
#define COLOR_RED 0xFF0000
#define COLOR_BLUE 0x0000FF
#define COLOR_GREEN 0x00FF00 
#define COLOR_AR_VISION 0x7FFF00 // YENİ: AR Vizyon Rengi (Parlak Yeşil)

// --- GLOBAL VİZYON SAYACI ---
static int about_click_count = 0; 
static int notification_timer = 0;
#define NOTIFICATION_DELAY_TICKS 420000 

// --- HARİCİ FONKSİYONLAR (Assembly'den Geliyor) ---
extern void enable_exception_handler(); 

// --- TEMEL GÜÇ VE GÜVENLİK ---
void log_message(const char* message, unsigned int color) { draw_string(50, 250, message, color); }
void adjust_volume_vision(int amount) { log_message("LOG: Ses ayarlama istegi alindi.", COLOR_WHITE); }

// --- TEMEL ÇİZİM FONKSİYONLARI ---
void draw_pixel(int x, int y, unsigned int color) {
    if (x >= 0 && x < 1024 && y >= 0 && y < 768) {
        unsigned int* vga = (unsigned int*)0xE0000000;
        vga[y * 1024 + x] = color;
    }
}
void draw_rect(int x, int y, int w, int h, unsigned int color) {
    for (int j = y; j < y + h; j++) {
        for (int i = x; i < x + w; i++) {
            draw_pixel(i, j, color);
        }
    }
}
void draw_char(int x, int y, char c, unsigned int color) { draw_rect(x, y, 8, 8, color); }
void draw_string(int x, int y, const char* str, unsigned int color) {
    int i = 0;
    int current_x = x;
    while (str[i] != '\0') {
        draw_char(current_x, y, str[i], color);
        current_x += 10; 
        i++;
    }
}


// --- PİC VE KESME YÖNETİMİ (Zorunlu) ---
void init_pic() {
    __asm__ __volatile__ ("outb %%al, $0x20" :: "a"(0x11));
    __asm__ __volatile__ ("outb %%al, $0xA0" :: "a"(0x11));
    __asm__ __volatile__ ("outb %%al, $0x21" :: "a"(0x20));
    __asm__ __volatile__ ("outb %%al, $0xA1" :: "a"(0x28));
    __asm__ __volatile__ ("outb %%al, $0x21" :: "a"(0x04));
    __asm__ __volatile__ ("outb %%al, $0xA1" :: "a"(0x02));
    __asm__ __volatile__ ("outb %%al, $0x21" :: "a"(0xFB)); 
    __asm__ __volatile__ ("outb %%al, $0xA1" :: "a"(0xEF)); 
}
void mouse_handler() {
    __asm__ __volatile__ ("outb %%al, $0x20" :: "a"(0x20));
    __asm__ __volatile__ ("outb %%al, $0xA0" :: "a"(0x20));
}
void get_current_time(int* hour, int* minute, int* second) { *hour = 17; *minute = 45; *second = 0; }
int get_battery_level() { return 0; }

// --- ÇEKİRDEK VİZYONU ---
void* malloc_vision(int size) {
    log_message("LOG: Dinamik bellek ayirma istegi alindi.", COLOR_BLUE);
    return (void*)0xDEADBEEF;
}
void create_thread_vision(void (*function)()) {
    log_message("LOG: Yeni is parcacigi olusturuldu.", 0x800080);
    function(); 
}

// --- KULLANICI UYGULAMA VİZYONLARI ---

// YENİ! Pionner AR (Artırılmış Gerçeklik) Vizyonu
void app_pionner_ar_start() {
    // Bu, geleceğe yönelik en büyük vizyondur!
    draw_string(50, 370, "PIONNER AR: Artirilmis Gerceklik Cekirdek Modu", COLOR_AR_VISION); 
}

// Diğer Tüm Uygulamalar (Sadece sadeleştirilmiş vizyon mesajları)
void app_settings_start() { 
    about_click_count++;
    draw_string(350, 50, "AYARLAR ACILDI", COLOR_WHITE);
}
void app_pionner_browser_start() { draw_string(50, 210, "PIONNER TARAYICI (Sanal Web)", 0x808080); }
void app_quickspace_start() { draw_string(50, 230, "QUICKSPACE: HIZLI AYARLAR", COLOR_BLUE); }
void app_pioneer_hub_start() { draw_string(50, 50, "PIONEER HUB BASLATILDI", COLOR_WHITE); }
void app_phonexy_ai_start() { draw_string(50, 70, "PHONEXY AI KERNEL AKTIF", COLOR_WHITE); }
void app_pionner_music_start() { draw_string(50, 90, "PIONNER MUSIC HAZIR", COLOR_WHITE); }
void app_pionner_translate_start() { draw_string(50, 110, "PIONNER CEVIRI BEKLEMEDE", COLOR_WHITE); }
void app_pionner_draw_start() { draw_string(50, 130, "PIONNER CIZIM HAZIR", COLOR_WHITE); }
void app_pionner_charge_start() { draw_string(50, 150, "PIONNER SARJ YONETIMI HAZIR", COLOR_WHITE); }
void app_pionner_file_start() { draw_string(50, 170, "PIONNER FILE EXPLORER HAZIR", COLOR_WHITE); }
void app_pionner_terminal_start() { draw_string(50, 190, "PIONNER TERMINAL BEKLEMEDE", COLOR_WHITE); }
void app_phonexy_files_start() { draw_string(50, 250, "PHONEXY DOSYALARIM: Bulut Depolama Hazir", 0xFF8C00); }
void app_pionner_messages_start() { draw_string(50, 270, "PIONNER MESAJLAR: Ag Baglantisi Kuruluyor", 0x4169E1); }
void app_pionner_qr_start() { draw_string(50, 290, "PIONNER QR TARAYICI: Kamera Erisim Vizyonu", 0x556B2F); }
void app_pionner_notes_start() { draw_string(50, 310, "PIONNER NOTLAR: Verimlilik Modu", 0xFFFF00); }
void app_calculator_start() { draw_string(50, 330, "HESAP MAKINESI: Matematik Motoru Hazir", 0x483D8B); }
void app_movies_tv_start() { draw_string(50, 350, "FILMLER & TV: Multimedya Akis Vizyonu", 0xDC143C); }


// --- ANA ÇEKİRDEK VE ARAYÜZ ---
void draw_pionner_launcher() {
    draw_rect(0, 0, 1024, 768, 0x00000000); 
    draw_rect(0, 0, 1024, 768, 0xFF7F50); 
    // İkonlar sadeleştirildi.
}


void kernel_main() {
    // KRİTİK BAŞLANGIÇ
    init_pic(); 
    __asm__ __volatile__("sti"); 
    
    // Uygulamaları Başlat
    draw_pionner_launcher(); 
    app_pioneer_hub_start(); 
    app_phonexy_ai_start();
    app_pionner_music_start(); 
    app_pionner_translate_start();
    app_pionner_draw_start();
    app_pionner_charge_start();
    app_pionner_file_start();
    app_pionner_terminal_start();
    app_quickspace_start();
    app_pionner_browser_start();
    app_phonexy_files_start(); 
    app_pionner_messages_start(); 
    app_pionner_qr_start(); 
    app_pionner_notes_start(); 
    app_calculator_start(); 
    app_movies_tv_start(); 
    app_pionner_ar_start(); // GERÇEKTEN SON VİZYON EKLEMESİ!

    // Çekirdek Vizyonları
    malloc_vision(1024); 
    
    // Sonsuz çekirdek döngüsü
    while(1) {
        int battery = get_battery_level();
        notification_timer++; 

        if (battery == 0) {
            draw_string(250, 300, "CIHAZINIZIN SARJI BITTI!", COLOR_RED); 
            draw_string(250, 320, "Sarja Takin Lutfen. Sarj uygulamasini acabilirsiniz.", COLOR_WHITE);
        }

        if (notification_timer == NOTIFICATION_DELAY_TICKS) {
            draw_string(600, 700, "BILDIRIM: Ag guncellemesi tamamlandi. (Gecikmeli)", COLOR_GREEN); 
        }
    }
}
