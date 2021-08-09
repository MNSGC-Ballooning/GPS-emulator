int semi = 0;
int col = 0;
int dec = 0;
int commaCheck = 0;
char dataPass[50];
int dataIndx[2] = {0, 0};
bool latcheck = false;


void dataSort(String pass) {

  String lati;
  String longi;
  String alti;

  String latiDEG;
  String latiMIN;
  String latiMINpass;
  String latiSEC;

  String longiDEG;
  String longiMIN;
  String longiMINpass;
  String longiSEC;

  for (int i = 0; i < pass.length() + 1; i++) { //get seperating comma chars and set semi & col to index

    dataPass[i] = pass.charAt(i);

    if ( dataPass[i] == ',') {
      commaCheck++;

      if (commaCheck == 1) {
        dataIndx[0] = i;
      }
      else if (commaCheck == 2) {
        dataIndx[1] = i;
      }
    }
    if (i == pass.length()) {
      dataPass[i] = '\0';
    }
  }
  commaCheck = 0;
  dataPass[dataIndx[0]] = ';';
  dataPass[dataIndx[1]] = ':';

  pass = String(dataPass);

  for (int i = 0; i < pass.length(); i++) {

    if (pass[i] == ';') {
      semi = i;
    }
    else if (pass[i] == ':') {
      col = i;
    }
  }

  lati = pass.substring(0, semi);
  longi = pass.substring((semi + 1), col);
  alti = pass.substring((col + 1));

  getDecIndx(lati);
  latcheck = true;
  latiDEG = lati.substring(0, dec); //get degree out of coordinate
  latiMINpass = lati.substring((dec)); //get decimal out of coordiante for minute converstion
  latiMIN = Convert2min(latiMINpass); // assign latiMIN to minute value
  latcheck = false;


  getDecIndx(longi);
  longiDEG = longi.substring(0, dec); //get degree out of coordinate
  longiMINpass = longi.substring((dec)); //get decimal out of coordiante for minute converstion
  longiMIN = Convert2min(longiMINpass); // assign latiMIN to minute value

  lati = (latiDEG + latiMIN);
  longi = (longiDEG + longiMIN);

  latf =  lati.toFloat();
  longf = longi.toFloat();


  if ( SDFlight == false) {
    
    if (altCommand == false)
      altf = ((alti.toFloat()) * 0.3048 - (ventBy) * 0.3048); //convert from ft to m minus the amount to be vented by
    else
      altf = (altSynth * 0.3048 - (ventBy) * 0.3048);

    sendGGA(GPGGA, 6);
    sendRMC(GPRMC, 6);
  }

  
  else {
    
    if (altCommand == false)
      altf = ((alti.toFloat()) * 0.3048 - (ventBy) * 0.3048); //convert from ft to m minus the amount to be vented by
    else
      altf = (HitAltf*0.3048 - (ventBy) * 0.3048); 
      altCommand = false; 

    sendGGA(GPGGA, 6);
    sendRMC(GPRMC, 6);
  }
}

String Convert2min(String hold) { //convert coordinate decimal to minute (UPDATE TO MAKE MORE ACCURATE (ROUDNING UP))
  float min = 0;
  String ripM;
  String ripm;
  String send;
  float cnvt = 0;

  cnvt = hold.toFloat();        //make coordinate decimal a float
  min = cnvt * 60;              //multiply by 60

  if ( latcheck == true) {


    if ( min < 10.00 ) {
      send = String(min);            //make float into string
      char addZero[send.length()];
      addZero[0] = '0';

      for (int i = 0; i < send.length() + 1; i++) {
        addZero[i + 1] = send.charAt(i);

      }

      send = String(addZero);
      ripM = send.substring(0, 2); //pull whole number
      ripm = send.substring (2); //pull decimal
      send = (ripM + ripm);     //seems redudant, but ensures when deciaml is 0 for longitude, it is not dumped. This will mess up the string
      return send;                  //send whole number (minute)
    }


    else {
      send = String(min);            //make float into string
    }

  }

  else if (latcheck == false) {
    if ( min < 9.996 ) {
      send = String(min);            //make float into string
      char addZero[send.length()];
      addZero[0] = '0';

      for (int i = 0; i < send.length() + 1; i++) {
        addZero[i + 1] = send.charAt(i);
      }

      send = String(addZero);
      ripM = send.substring(0, 2); //pull whole number
      ripm = send.substring (2);
      send = (ripM + ripm);
      return send;                  //send whole number (minute)
    }

    else {
      send = String(min);            //make float into string

    }
  }
}
/*
  String Convert2sec(String hold) { //convert coordinate decimal to second (UPDATE TO MAKE MORE ACCURATE (ROUDNING UP))
  float sec = 0;
  String rip;
  String send;
  float cnvt = 0;

  cnvt = hold.toFloat();        //make coordinate decimal a float
  sec = cnvt * 60;              //multiply by 60 to get minute (whole #)
  rip = String(sec);            //make float into string
  send = rip.substring((dec));  //pull decimal of string
  sec = (send.toFloat() * 60);  //convert to float, mult. by 60 to get seconds
  rip = String(sec);            //convert float into string
  send = rip.substring(0, dec); //get only whole number of second
  return send;                  //send second
  }


*/
void getDecIndx(String hold) {  //get index of decimal point
  for (int i = 0; i < hold.length(); i++) {

    if (hold[i] == '.') {

      dec = i;
    }
  }

}
