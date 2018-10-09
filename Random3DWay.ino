
#define DS_pin 4
#define STCP_pin 5
#define SHCP_pin 6

int posX=0;
int posY=0;
int posZ=0;

#define ship 0

int Arreglo[16];
int contador=0;

int Matrix[3][4][4][4]=
{
  {
    {
      {1,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    } 
  },
  {
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,1,1,0},
      {0,1,1,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,1,1,0},
      {0,1,1,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    }
  },
  {
    {
      {1,1,1,1},
      {1,0,0,1},
      {1,0,0,1},
      {1,1,1,1}
    },
    {
      {1,1,1,1},
      {1,0,0,1},
      {1,0,0,1},
      {1,1,1,1}
    },
    {
      {1,1,1,1},
      {1,0,0,1},
      {1,0,0,1},
      {1,1,1,1}
    },
    {
      {1,1,1,1},
      {1,0,0,1},
      {1,0,0,1},
      {1,1,1,1}
    } 
  },
};

void setup()
{
  for(int i=0; i<7;i++){
    pinMode(i, OUTPUT);
  }
  randomSeed(analogRead(0));
}

void ShiftRegister(){
  digitalWrite(STCP_pin, LOW);
    for(int i=15; i>=0; i--){
      digitalWrite(SHCP_pin, LOW);
        digitalWrite(DS_pin, Arreglo[i]);
        digitalWrite(SHCP_pin, HIGH);
    }
    digitalWrite(STCP_pin, HIGH);
}

void Mover(){
  MoverPos(random(8,14));  
}


void MoverPos(int i){
  switch(i){
    case 13:posX--;
          break;
  case 11:posY++;
          break;
  case 12:posY--;
          break;
  case 10:posX++;
          break;
  case 9: posZ++;
          break;
  case 8: posZ--;
        break;
  }
  posX = constrain(posX,0,3);
  posY = constrain(posY,0,3);
  posZ = constrain(posZ,0,3);
}

void limpiar(int Nivel){
    contador=0;
    for(int x=0; x<16;x++)
      Arreglo[x]=0;
    ShiftRegister();
    digitalWrite(Nivel, HIGH);
}

void limpiar3D(){
  for(int z=0; z<4; z++)
    for(int x=0; x<4; x++)
      for(int y=0; y<4; y++)
                Matrix[ship][z][y][x]=0;
}


void loop()
{ 
 for(int scan=0; scan<200; scan++){
  for(int Nivel=0; Nivel<4; Nivel++){
    for(int i=0; i<4; i++)
      for(int j=0; j<4; j++){
        Arreglo[contador]=Matrix[ship][Nivel][i][j];
        contador++;
      }
    ShiftRegister();
    digitalWrite(Nivel, LOW);
    limpiar(Nivel);
  }
 }
  Mover();
  limpiar3D();
  Matrix[ship][posZ][posY][posX]=1;
}
