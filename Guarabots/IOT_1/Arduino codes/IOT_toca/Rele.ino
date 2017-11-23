void controle_RELE(void) {
  //Controle Rele 1___________________________________
  if (readString.indexOf("?ligar") > 0) {
    estado_Rele(pino_rele1, LOW);
    ligado = false;
  } else if (readString.indexOf("?desligar") > 0) {
    estado_Rele(pino_rele1, HIGH);
    ligado = true;
  }

  //Controle Rele 2___________________________________
  if (readString.indexOf("?2_ligar") > 0) {
    estado_Rele(pino_rele2, LOW);
    ligado_2 = false;
  } else if (readString.indexOf("?2_desligar") > 0) {
    estado_Rele(pino_rele2, HIGH);
    ligado_2 = true;
  }
}
