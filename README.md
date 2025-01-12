# MaviOS

MaviOS, minimalist ve özelleştirilebilir bir Linux dağıtımı oluşturmayı amaçlayan bir projedir. Bu proje, yüksek lisans çalışmanız sırasında ek olarak geliştirilmiştir.

## İçindekiler

- [Özellikler](#özellikler)
- [Kullanılan Teknolojiler](#kullanılan-teknolojiler)
- [Gereksinimler](#gereksinimler)
- [Kurulum](#kurulum)
- [Kullanım](#kullanım)
- [Katkıda Bulunma](#katkıda-bulunma)
- [Lisans](#lisans)

## Özellikler

- **Minimalist Yapı:** Gereksiz bileşenlerden arındırılmış, sadece temel işlevleri içeren hafif bir sistem.
- **Özelleştirilebilirlik:** Kullanıcıların ihtiyaçlarına göre yapılandırılabilir ve genişletilebilir bir altyapı.
- **Kolay Çalıştırma:** ISO dosyası ve `run.sh` betiği ile hızlı bir şekilde başlatılabilir.
- **Yüksek Performans:** Düşük donanım gereksinimlerine rağmen etkili bir sistem.

## Kullanılan Teknolojiler

- **Linux Kernel:**  
  MaviOS’un temelini oluşturan Linux çekirdeği, minimalist bir yapılandırma ile gereksiz modüllerden arındırılmıştır.

- **BusyBox:**  
  BusyBox, temel Unix araçlarını tek bir ikili dosyada birleştirerek sistem boyutunu küçültür ve kullanım kolaylığı sağlar.

- **glibc:**  
  C kütüphanesi olarak glibc kullanılmıştır. Bu, çekirdek ve uygulama seviyesinde temel işlevlerin sağlanmasına olanak tanır.

Bu teknolojiler bir araya gelerek hafif, hızlı ve özelleştirilebilir bir sistem oluşturur.

## Gereksinimler

- **Donanım:** Temel donanım gereksinimleriyle çalışacak şekilde tasarlanmıştır.
- **Yazılım:** Linux çekirdeği ve temel GNU araçları gerektirir.

## Kurulum

1. **Depoyu Klonlayın:**

   ```bash
   git clone https://github.com/0x421F/MaviOs.git
   cd MaviOs
   ```

2. **Yapı Betiğini Çalıştırın (Opsiyonel):**

   Eğer ISO dosyasını sıfırdan oluşturmak isterseniz, şu komutları kullanabilirsiniz:

   ```bash
   chmod +x build.sh
   ./build.sh
   ```

   Bu betik, gerekli dosyaları derleyerek `mavi.iso` dosyasını oluşturacaktır.

## Kullanım

### 1. **Hazır ISO Dosyasını Çalıştırma:**

Depoda bulunan `mavi.iso` dosyasını ve `run.sh` betiğini kullanarak sistemi başlatabilirsiniz:

```bash
chmod +x run.sh
./run.sh
```

Bu betik, sanal bir makine ortamında `mavi.iso` dosyasını çalıştıracaktır.

### 2. **Manuel Çalıştırma:**

QEMU kullanarak ISO dosyasını manuel olarak başlatabilirsiniz:

```bash
qemu-system-x86_64 -cdrom mavi.iso -boot d
```

### 3. **Kendi ISO Dosyanızı Oluşturma:**

Eğer sistemi özelleştirerek yeni bir ISO dosyası oluşturmak isterseniz, `build.sh` betiğini çalıştırdıktan sonra yukarıdaki yöntemlerle yeni ISO dosyanızı çalıştırabilirsiniz.

## Lisans

Bu proje [MIT Lisansı](LICENSE) ile lisanslanmıştır.
