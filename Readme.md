# 🚀 PionnerOS - Orbital: Nihai Vizyon Çekirdeği

## Proje Vizyonu
PionnerOS - Orbital, C diliyle sıfırdan yazılmış, temel bir işletim sistemi çekirdeğinin tüm mimari gereksinimlerini sergilemek üzere tasarlanmış bir projedir. Bu proje, donanım karmaşasına girmeden, **OS geliştirme mantığını** ve temel çekirdek fonksiyonlarını (Bellek Yönetimi, Sürücü Vizyonları, Görev Yönetimi) tek bir projede mühürler.

---

## ✅ Proje Durumu ve Özellikleri

| Özellik | Durum | Açıklama |
| :--- | :--- | :--- |
| **Kodlama** | Tamamlandı | Çekirdek kodlama aşaması bitmiştir. |
| **Çekirdek Dili** | C | Projenin tamamı C dili kullanılarak geliştirilmiştir. |
| **Sanal Makine** | Uyumlu | QEMU ve VirtualBox gibi ortamlarda test edilmiştir. |

---

## 💾 PionnerOS'u Çalıştırma Talimatları (Kullanıcılar İçin)

PionnerOS'u test etmek için **ISO dosyasını indirmeli** ve bir sanal makine kurmalısınız.

### ADIM 1: Gerekli Yazılımı Kurun (QEMU)
QEMU, bu tür çekirdekleri çalıştırmak için ideal araçtır.
* **Linux/Ubuntu:** Terminale `sudo apt install qemu-system-x86` komutunu girin.
* **Windows/macOS:** [QEMU resmi web sitesinden](https://www.qemu.org/download/) indirin.

### ADIM 2: ISO Dosyasını İndirin
1.  Bu depoda bulunan **PionnerOS ISO dosyasını** (muhtemelen `PionnerOS-Orbital.iso` adıyla) indirin.
2.  Dosya, **[Releases (Sürümler)](https://github.com/yusuf1905emre1905-byte/PionnerOS-Orbital/releases)** sekmesinde veya ana dosya listesinde bulunabilir.

### ADIM 3: Terminalden Çalıştırın
ISO dosyasını indirdiğiniz klasörde bir terminal açın ve aşağıdaki komutu girin:

```bash
qemu-system-i386 -cdrom PionnerOS-Orbital.iso
