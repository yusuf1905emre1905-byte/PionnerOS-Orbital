# PionnerOS-Orbital
# 💻 PIONNEROS PC EDITION (KOD ADI: ORBITAL)

**Sıfırdan Yazılmış (From-Scratch) x86 Masaüstü İşletim Sistemi Projesi**

---

## ✨ Proje Vizyonu

PionnerOS, mevcut işletim sistemlerinin mimarisine meydan okuyan, temiz, modern ve **güvenlik odaklı** bir OS konseptidir. Bu proje, C ve Assembly dilleri kullanılarak düşük seviyede yazılmış bir çekirdeğin, grafik arayüzleri ve uygulama iskeletlerini nasıl barındırabileceğini göstermeyi amaçlamaktadır.

## 🌟 Temel Özellikler

* **Sunset Launcher:** Dinamik gradyan (Güneş Batımı) temalı, görsel olarak zengin ana ekran.
* **Mimari Derinlik:** Çekirdek seviyesinde **Bellek Koruma** ve **Hata Yakalama (Exception Handling)** için uygulama iskeletleri mevcuttur.
* **Uygulama İskeletleri:**
    * **Pioneer Hub:** Uygulama mağazası mimarisi.
    * **PhonexyAI:** Yapay zeka asistanı başlangıç mantığı.
    * **P. Music, P. Ceviri, P. Çiz:** Multimedya ve veri güvenliği mantıklarını içeren iskeletler.
* **Çekirdek Temeli:** 16-bit Assembly'den 32-bit Korumalı Moda başarılı geçiş.

## ⚠️ Çalıştırma Uyarısı (Geliştirici Önyükleme Ortamı)

PionnerOS bir uygulama değildir; bu, bilgisayarın tüm donanımını kontrol etmesi gereken bir çekirdek projesidir. **Kalıcı donanım hasarını önlemek ve stabilite sağlamak için güvenli bir Önyükleme Ortamında (QEMU/VirtualBox) çalıştırılmalıdır.**

### Çalıştırma Komutları

1.  Gerekli araçları (QEMU, NASM, GCC) kurun.
2.  Projeyi indirin ve klasöre girin.
3.  **Derleme ve Başlatma:**
    ```bash
    make
    make run
    ```
---
