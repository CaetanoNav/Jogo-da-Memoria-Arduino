#define led1 2
#define led2 3
#define led3 4
#define led4 5
#define bot1 6
#define bot2 7
#define bot3 8
#define bot4 9
#define busina 10
#define botini 11

//Variaveis Busina
int doNote = 262; // Dó
int reNote = 294; // Ré
int miNote = 330; // Mi
int faNote = 349; // Fá
int solNote = 392; // Sol
int laNote = 440; // Lá
int siNote = 494; // Si

//Variaveis para a máquina
const int turnos_max = 50; 
int turnos[turnos_max];
int len = 0; //index, para ter controle das posições

//Variaveis para o jogador
int turno_j[turnos_max];
int len_j = 0;
int led_esc[4] = {2,3,4,5}; // lista de leds disponiveis para o jogador
int escolha; //led escolhido da lista

//Funções
void somLed(int led){
  if(led == led1) tone(busina, doNote, 200);
  if(led == led2) tone(busina, reNote, 200);
  if(led == led3) tone(busina, miNote, 200);
  if(led == led4) tone(busina, faNote, 200);
}
void (*funcReset)()=0;
void ligaPino(int pino){
  digitalWrite(pino, HIGH);
}
void deslPino(int pino){
  digitalWrite(pino, LOW);
}
void piscaLed(int led){
  ligaPino(led);
  somLed(led);
  delay(500);
  deslPino(led);
  delay(500);
}
void ganhou(){ //Função quando passa de turno
  for(int x = 2; x < 6; x++){
    ligaPino(x);
  }
  tone(busina, solNote, 400);
  delay(400);
  tone(busina, miNote, 400);
  delay(400);
  tone(busina, doNote, 400);
  delay(400);
  tone(busina, siNote, 400);
  delay(400);
  for(int x = 2; x < 6; x++){
   deslPino(x);
  }
}
void musicaDerrota(){
  tone(busina, siNote, 300);
  delay(300);
  tone(busina, solNote, 300);
  delay(300);
  tone(busina, miNote, 300);
  delay(300);
  tone(busina, doNote, 600);
  delay(600);
  noTone(busina);
}
void musicaInicio(){
  tone(busina, doNote, 200);
  delay(250);
  tone(busina, doNote, 200);
  delay(250);
  tone(busina, solNote, 200);
  delay(250);
  tone(busina, solNote, 200);
  delay(250);
  tone(busina, laNote, 200);
  delay(250);
  tone(busina, laNote, 200);
  delay(250);
  tone(busina, solNote, 400);
  delay(500);
  noTone(busina);
}
void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(bot1, INPUT);
  pinMode(bot2, INPUT);
  pinMode(bot3, INPUT);
  pinMode(bot4, INPUT);
  pinMode(busina, OUTPUT);
  pinMode(botini, INPUT);
  
  randomSeed(analogRead(A0));
  
  musicaInicio();
  piscaLed(led1);
  piscaLed(led4);
  piscaLed(led3);
  piscaLed(led2);
  
}

void loop()
{
  if(digitalRead(botini) == LOW){
    delay(500);
    while (true){

      int num_alea = random(2, 6); //Gerando um numero aleatório
      turnos[len] = num_alea; len++; //Armazando o numero gerado, em seguida muda de casa
      for (int a = 0; a <= len-1; a++){
        int led = turnos[a];
        piscaLed(led);
      }

      for (int b = 0; b <= len-1; b++){
        while(digitalRead(bot1) == HIGH && digitalRead(bot2) == HIGH && digitalRead(bot3) == HIGH && digitalRead(bot4) == HIGH) {
        //Enquanto nenhum dos botoes n for pressionado ele fica parado
        }
        if(digitalRead(bot1) == LOW){
          piscaLed(led1);
          escolha = led_esc[0];
        }
        if(digitalRead(bot2) == LOW){
          piscaLed(led2);
          escolha = led_esc[1];
        }
        if(digitalRead(bot3) == LOW){
          piscaLed(led3);
          escolha = led_esc[2];
        }
        if(digitalRead(bot4) == LOW){
          piscaLed(led4);
          escolha = led_esc[3];
        }
        turno_j[len_j] = escolha; len_j++;
        //Caso o jogador erre
        for( int c = 0; c <= len_j-1; c++){
          if(turnos[c] != turno_j[c]){
            musicaDerrota();
            funcReset();
          }
        }
      }
      //zerando a lista do jogador para uma próxima rodada
      len_j = 0;
      ganhou();

      delay(1000);
    }
  }
}