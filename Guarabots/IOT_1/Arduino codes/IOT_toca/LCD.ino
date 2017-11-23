void controle_LCD(void){
  if(msgPersonalizada){
    webMessage();
  }else{
    temometro_LCD();
  }
}

void webMessage(void){
  //Imprime msg na tela___________________________________
  if (readString.indexOf("msg=") > 0) {
    lcd.clear();
    String reciveMensage;
    int i = msgBegin;
    while (readString[i] != ' ') {
      reciveMensage += readString[i];
      i++;
    }
    lcd.print(reciveMensage);
    msgPersonalizada = true;
  }
}

void temometro_LCD(void) {
  lcd.setBacklight(HIGH);
  lcd.setCursor(3, 0);
  lcd.print("GuaraBots");
  lcd.setCursor(1, 1);

  lcd.print("temp: ");
  lcd.print(leituraPorta[3] / 340.00 + 36.53);
  lcd.print("C");
}
