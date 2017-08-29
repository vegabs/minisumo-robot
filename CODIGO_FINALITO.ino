
int estado=0;
int velo=190;  
int velogiro=100;  
int veloataque=255;
int var=0;
int var1=1;

//PINS: ULTRASONIDO
int trig=4;
int echo=3;

//PINS MOTOR A
int a1=9;
int a2=10;
int eA=11; //PIN ENABLE PARA L298N

//piNS motor B
int a3=6;
int a4=7;
int eB=5; //PIN ENABLE PARA L298N

/////////////////////////////////////////////////////////////////////////////////////////

void adelante(){
  digitalWrite(a1,HIGH); digitalWrite(a2,LOW); analogWrite(eA,velo);
  digitalWrite(a3,HIGH); digitalWrite (a4, LOW); analogWrite(eB,velo);
  
  
}

void atras(){
  digitalWrite(a1,LOW); digitalWrite(a2,HIGH); analogWrite(eA,250);
  digitalWrite(a3,LOW); digitalWrite (a4,HIGH); analogWrite(eB,250);

}

void parada(){
  digitalWrite(a1,LOW); digitalWrite(a2,LOW); analogWrite(eA,velo);
  digitalWrite(a3,LOW); digitalWrite (a4,LOW); analogWrite(eB,velo);

}

void derecha(){ 
  digitalWrite(a1,HIGH); digitalWrite(a2,LOW); analogWrite(eA,velogiro);
  digitalWrite(a3,LOW); digitalWrite (a4,LOW); analogWrite(eB,velogiro);

  
}

void izquierda(){ 
  digitalWrite(a1,LOW); digitalWrite(a2,LOW); analogWrite(eA,velogiro);
  digitalWrite(a3,HIGH); digitalWrite (a4,LOW); analogWrite(eB,velogiro);

}


void ataque(){
  digitalWrite(a1,HIGH); digitalWrite(a2,LOW); analogWrite(eA,veloataque);

}

//////////////////////////////////////////////////////////////////////////////////////////7

void setup (){
   
    
  
  

  
  Serial.begin(9600); 
  
  //ULTRASOUND PINS
  pinMode(trig,OUTPUT); 
  pinMode(echo,INPUT);
  
  //MOTOR PINS 
  pinMode(a1,OUTPUT);  pinMode(a2,OUTPUT);  pinMode(eA,OUTPUT);
  pinMode(a3,OUTPUT);  pinMode(a4,OUTPUT);  pinMode(eB,OUTPUT);
  
  
  
}

//////////////////////////////////////////////////////////////////////////////////////////////

void loop (){

  //PARA LOS SENSORES CNY70
  int dato=analogRead(A0);
  int dato1=analogRead(A1);
  

 //DISTANCIA
  digitalWrite(trig,LOW); delayMicroseconds(4);
  digitalWrite(trig,HIGH); delayMicroseconds(10);
  digitalWrite(trig,LOW);
  int duracion=pulseIn(echo,HIGH);
  int distancia=duracion/29/2;

///////////////////////////////////////////////////////////////////////////////////////////////////
  //MANUAL MODE

  if(Serial.available()>0)
  {estado = Serial.read(); }


  if(estado=='1'){adelante();} 
  if(estado=='2'){atras();} 
  if(estado=='3'){parada();} 
  if(estado=='4'){derecha();} 
  if(estado=='5'){izquierda();}
  if(estado=='7'){ataque();}

/////////////////////////////////////////////////////////////////////////////////////////////////

  //MODO AUTOMATICO

  
  if(Serial.available()>0)
  {estado = Serial.read();}

  if(estado=='8')
  { 
    if(var1==1){
      //tiempo de seguridad
     delay(5000);
     var1=2;
    }
    if(distancia>0 && distancia<=70) { if(var==0) { derecha(); delay(150); var=1; 

    }
    adelante(); if(distancia>=0 && distancia<=30) {ataque(); }}
    

    else { var=0; izquierda();
  
    
       } 

///////////////////////////////////////////////////////////////////

        //SENSOR ADELANTE: SI EL COLOR ES BLANCO RETROCEDES POR 500 Y TE VAS A LA DERECHA Y ADELANTE
        if(dato<=500 || dato1<=500){ atras();
        digitalWrite(8,HIGH);
        digitalWrite(12,HIGH);
        digitalWrite(2,LOW);
        digitalWrite(13,LOW);
        delay(500);}
       
        
        
        
       
  }  
}

