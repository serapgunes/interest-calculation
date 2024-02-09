#include <stdio.h>
#include <math.h>


void print_duration(int ay) {
    int yil = ay / 12;// önce verilen "ay" değerini 12'ye bölünüyor ve yıl değeri elde ediliyor.
    // Yani ay'15 değeri yazılırsa eğer 1 yıl 3 ay şeklinde olmasını sağlayacak.
    int kalan_ay = ay % 12;//"ay" değerinin 12'ye bölümünden kalanını hesaplayıp elde etmek için bu kodu kullanıyoruz.
    printf("Year:%d, month:%d\n", yil, kalan_ay);
}

void print_money(float miktar) {
    printf("%.1f$\n", miktar);//miktar değerini float cinsinden ve $ işaretiyle birlikte yazdıracak.
}

void print_entry(float kredi_tutari, float aylik_odeme, int ay) {
    printf("-> ");
    print_duration(ay);// yıl ve ay'ı gösterecek olan kodu çağırır.

    printf("Total payment:\n ");
    print_money(kredi_tutari);//bu kod krediyi hesaplamış olan print_money fonksiyonunu çağırır.

    printf("Monthly payment:\n ");
    print_money(aylik_odeme);//aylık ödemenin hesaplandığı kodu çağırıyoruz.

    printf("----------------------------------------\n");
    printf("----------------------------------------\n");

}

void print_full_report(float kredi_tutari, float yillik_faiz_orani, int maksimum_yil, int maksimum_ay, int yineleme_araligi) {//bu fonksiyon için kullanacağımız tanımlar.
    float aylik_faiz_orani = yillik_faiz_orani / 12 / 100;//önce yıllık faiz oranını aylık faiz oranına dönüştürüyoruz
    //daha sonra aşağıdaki kodlarda her bir ay için faiz hesaplaması yapılacak.
    int toplam_ay = maksimum_yil * 12 + maksimum_ay;//Burada,girilen maksimum yıl ve maksimum ay değerlerine dayanarak toplam ay sayısını hesaplıyoruz.
    // maksimum yılı 12 ile çarparak yılları aylara dönüştürüyoruz ve maksimum ay değerini ekleyerek toplam ay sayısını elde ediyoruz.
    // Toplam ay sayısı bize faizi kaç aya böleceğimizi hesaplayabilmek için gereklidir.
    float bakiye = kredi_tutari;

    printf("----------------------------------------\n");

    int gecerli_aralik = yineleme_araligi;//gecerli aralık artış miktarını kendimizin belirlediği yineleme aralığına eşitliyoruz.
    int gecerli_ay = 0;//bu kodda da ay miktarı artarken önce sıfırı alsın daha sonra artış miktarına göre artsın diye sıfırla başlattım.

    while (gecerli_ay < toplam_ay) {//buradaki while döngüsü her bir ay için ödemeyi hesaplayacak ve gecerli_ay
        // yani en başta girilen ay sayısı toplam_ay dan küçük olana kadar işlemi yapacak ve aylık ödemeyi rapor halinde yazdırıcak.
        float aylik_odeme = bakiye / (gecerli_ay);//burada bakiye kredi tutarımızdır, bakiye'yi istenilen ay sayısına böldüğümüzde
        // her bir ay için bize aylık ödemeyi hesaplayacak.

        if (gecerli_ay == gecerli_aralik) {//mevcut olan ay ile arttıracağımız ay aynı olunca if'in içerisine giriyoruz
            print_entry(bakiye, aylik_odeme, gecerli_ay);
            gecerli_aralik += yineleme_araligi; //gecerli aralık değerini yineleme aralığı kadar arttırıyoruz yani yazdırılacak rapor da
            // örneğin yineleme aralığı 2 ise rapor 2 ay da bir şeklinde olacak.
            }

        float faiz = bakiye * aylik_faiz_orani;//önceden yıllık faizi aylık faize dönüştürmüştük şimdi bu kodlada her bir ay için gelecek
        //faiz hesaplamasını yapıyoruz her bir ay sonunda faiz ödemesi yapılmış olacak.
        bakiye += faiz;//faiz miktarını bakiyemize ekliyoruz.
        gecerli_ay++;//bir sonraki ay'a geçmek için geçerli ay'ı arttırıyoruz.
    }
    float aylik_odeme = bakiye / toplam_ay;//aylık ödemeyi hesaplarken toplam faizli olan bakiyemizi toplam ay'a bölüyoruz.
    // Bunu ayrıyeten yapmamızın sebebi gecerli ay yoplam ay dan küçük olana kadar yukarıdaki işlemi yapacak yani son aya geldiğinde
    // onun için bir işlem gerçekleşmeyecek en sonuncu aya geldiğinde burada yazdığımız kod hesaplama yapacak.
    print_entry(bakiye, aylik_odeme, toplam_ay);
}

int main() {
    char ad[100];
    float yillik_faiz_orani;
    float kredi_tutari;
    int maksimum_yil;
    int maksimum_ay;
    int yineleme_araligi;

    printf("......................................................\n");
    printf(".*.*.*.*.*Welcome to the Interest Calculator*.*.*.*.*.\n");
    printf("......................................................\n\n");

    printf("Please enter your name: ");
    scanf("%s", ad);

    printf("Loan amount: ");
    scanf("%f", &kredi_tutari);

    printf("Interest rate (per year): ");
    scanf("%f", &yillik_faiz_orani);

    printf("Loan term in years: ");
    scanf("%d", &maksimum_yil);

    printf("Loan term in months: ");
    scanf("%d", &maksimum_ay);

    printf("Iteration in months:");
    scanf("%d", &yineleme_araligi);

    printf("\n");
    printf("Report for: %s\n", ad);

    print_full_report(kredi_tutari, yillik_faiz_orani, maksimum_yil, maksimum_ay, yineleme_araligi);

    return 0;
}
