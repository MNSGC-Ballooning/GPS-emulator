void Fix(){
  static long r;
  r = random(1,101);
  if(r<=2){
    fix = false;
  }
  else{
    fix = true;
  }
  
}

