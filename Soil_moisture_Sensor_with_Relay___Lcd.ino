#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // عنوان I2C الصحيح

‎// تعريف مدخل حساس الرطوبة
int moistureSensorPin = A0;  // الحساس متصل بالمدخل التماثلي A0
int moistureValue = 0;       // متغير لحفظ قيمة الرطوبة

void setup() {
  lcd.begin(16, 2);           // شاشة بحجم 16 عمود و2 صف
  lcd.backlight();            // تفعيل إضاءة الخلفية
  lcd.clear();                // مسح الشاشة من أي بيانات قديمة
  
‎  // تهيئة المنفذ التسلسلي لمراقبة القيم في الشاشة التسلسلية
  Serial.begin(9600);
  
‎  // عرض رسالة على الشاشة عند البدء
  lcd.setCursor(0, 0);        // وضع المؤشر في العمود الأول، الصف الأول
  lcd.print("Moisture Level:"); // طباعة عنوان
}

void loop() {
‎  // قراءة قيمة الرطوبة من الحساس
  moistureValue = analogRead(moistureSensorPin);
  
‎  // تحويل القيمة إلى نسبة مئوية
  int moisturePercent = map(moistureValue, 1023, 0, 0, 100); // تحويل القيمة إلى نسبة
  
‎  // عرض قيمة الرطوبة على شاشة LCD
  lcd.setCursor(0, 1);         // وضع المؤشر في العمود الأول، الصف الثاني
  lcd.print("                ");  // مسح أي بيانات سابقة في الصف
  lcd.setCursor(0, 1);         // إعادة وضع المؤشر في الصف الثاني
  lcd.print(moisturePercent);  // طباعة نسبة الرطوبة
  lcd.print("%");

‎  // عرض القيمة في الشاشة التسلسلية أيضًا
  Serial.print("Moisture: ");
  Serial.print(moisturePercent);
  Serial.println("%");
  
‎  // تأخير لتحديث البيانات كل ثانية
  delay(1000);
}
