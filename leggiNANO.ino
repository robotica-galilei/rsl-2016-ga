int leggiNANO(int &o,int &v){
  char chr;
  while (Serial2.available()){
    chr=Serial2.read();}                          //Pulisce il buffer
  String str="";
  while(true) {
    chr=Serial2.read();
    if (chr=='#')                             //Va a cercare il carattere #
      break;
  }
  while(chr!=',') {                        //Finchè non trova il carattere ,
    if(Serial2.available()) {
      chr=Serial2.read();
      str+=chr;                           //Legge e assegna alla stringa il carattere
    }
  }
  o=str.toInt();                        //Trasforma la stringa in intero
  str="";
  while(chr!='#') {
    if(Serial2.available()) {               //Come prima, ma fino a #
      chr=Serial2.read();
      str+=chr;
    }
  }
  v=str.toInt();
}
