void Fix(){
  static long r;
  r = random(1,101);
  if(r<=10){
    fix = false;
  }
  else{
    fix = true;
  }
  
}

