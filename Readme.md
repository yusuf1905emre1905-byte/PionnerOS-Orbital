# 🚀 PionnerOS: Bir İşletim Sistemi Çekirdeği (v1.2.0)

PionnerOS, sıfırdan C ve Assembly dilleri kullanılarak geliştirilen, modern işletim sistemlerine alternatif olma vizyonuyla yola çıkan bir **32-bit (i386) İşletim Sistemi Çekirdeği** projesidir.

Bu proje, bir simülasyon değil, **gerçek donanım üzerinde çalışabilen**, temel OS bileşenlerini barındıran tam teşekküllü bir sistemdir.

---

## 🎯 Vizyon ve Misyon

**Misyon:** PionnerOS, kullanıcılarına Linux veya Windows gibi kurulu sistemlere bağımlı kalmadan, **doğrudan donanım seviyesinde çalışan** hızlı, hafif ve güvenli bir alternatif sunmayı amaçlar. Tıpkı **LineageOS'un Android'i devraldığı gibi**, PionnerOS da bilgisayarınızı temelden devralmak için tasarlanmıştır.

**Hedef Kitle:** Bilgisayarın çekirdek seviyesindeki işleyişini merak eden geliştiriciler, üniversite projeleri ve eski, 32-bit donanımlara hayat vermek isteyen teknoloji meraklıları.

---

## ✨ Çekirdek Özellikler (Pionner Gücü)

PionnerOS, basit bir terminal uygulamasının çok ötesinde, kritik OS görevlerini yerine getirir:

| Özellik Alanı | İçerik | Teknik Gerçeklik |
| :--- | :--- | :--- |
| **Donanım Erişimi** | **RTC (Saat) Entegrasyonu:** CMOS yongasından gerçek zamanı okur ve sürekli günceller. | **Doğrudan I/O Portu Erişimi** (`inb/outb`). |
| **Girdi Yönetimi** | **Türkçe Klavye Sürücüsü:** Q, W, E, R... ve **Ö, Ç, Ş, İ, Ğ, Ü** karakterlerini destekler. | **Ham Scancode İşleme**, mevcut işletim sisteminden bağımsız. |
| **Bellek Yönetimi** | **Dinamik Heap (Yığın) Ayırma:** Uygulamaların güvenli ve izole bir şekilde bellek kullanmasını sağlar (`malloc/free`). | **Kritik OS Kararlılığı** ve Uygulama İzolasyonu. |
| **Güvenlik/İzolasyon**| **GDT (Global Tanımlayıcı Tablosu):** İşlemciyi korumalı moda geçirerek güvenliğin temelini atar. | **Çekirdek Düzeyinde Güvenlik İskeleti.** |
| **Kullanıcı Deneyimi** | **Kaydırma (Scrolling) Desteği:** 25 satırdan fazla metni otomatik olarak yukarı kaydırır. | **VGA Belleği Manipülasyonu** (`0xB8000`). |
| **Uygulama Yönetimi** | **Pionner HUB:** Uygulamaları kurma (`INSTALL`), kaldırma (`UNINSTALL`) ve başlatma yeteneği. | **Uygulama Envanteri Veritabanı** yönetimi. |

---

## 🛠️ Kurulum ve Çalıştırma (Oyun Başlasın!)

PionnerOS, gerçek bir çekirdek olduğu için, normal bir program gibi çalıştırılamaz. **Donanımı devralması** gerekir.

**1. Gerekenler:**
* `kernel.c` (Bu dosya)
* `linker.ld` (Bellek haritası)
* `grub.cfg` (Yükleyici yapılandırması)
* Bir **32-bit (i386)** ortamı.

**2. Test Ortamı (Önerilen):**
Projenin **kusursuz ve hatasız** çalıştığından emin olmak için QEMU (sanallaştırma yazılımı) önerilir.

```bash
# Çekirdeği derle (GCC i386-elf ile)
i386-elf-gcc -m32 -c kernel.c -o kernel.o -std=gnu99 -ffreestanding
i386-elf-ld -m elf_i386 -T linker.ld kernel.o -o PionnerOS.bin

# ISO dosyasını oluştur
# ... (ISO oluşturma adımları buraya eklenir)

# QEMU ile başlat
qemu-system-i386 -kernel PionnerOS.bin
