#include <LiquidCrystal.h>
#include <string.h>
#include <stdio.h>

//Variaveis globais
int count = 0;
char letra[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','x','z','y','w'};
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
bool state = false;
char wd[] = "abc";
char filter[16];
int loser = 2;
int choise;
//Função de configuração unica
void setup() {

  for(int i = 0; i<strlen(wd); i++)
  filter[i]='_';


  pinMode(6,INPUT_PULLUP);
  pinMode(7,INPUT_PULLUP);
  pinMode(9,INPUT_PULLUP);
  lcd.begin(16,2);
  lcd.print("Bem vindo!");
  lcd.setCursor(0,1);
  lcd.print("#Jogo da forca#");

}
//Função loop do arduino que ferra com todo o esquema
void loop() {
  int stateUp = digitalRead(6);
  int stateDown = digitalRead(7);
  int stateSelect = digitalRead(9);

  //Verifica o estado inverso dos botoes, se true, executam suas tarefas
  if(stateUp == 0){
    selectUp();
    delay(300);
  }

  if(stateDown == 0){
    selectDown();
    delay(300);
  }
  if(stateSelect == 0){
    selectChar();
    delay(300);
  }
}
//Função de escolha up - Hardware
void selectUp(){
  state = true;
  lcd.begin(16,2);
  lcd.print("Esco. a letra: ");
  lcd.setCursor(5,1);
  lcd.print(letra[count]);
  count++;
}
//Função de escolha down - Hardware
void selectDown(){
  state = false;
  lcd.setCursor(5,1);
  count--;
  lcd.print(letra[count]);
}
//Função de seleção da letra - Hardware
void selectChar(){
  if(state)
  count--;
  validateTest(letra[count]);
}

//Função de validação - Regra de negocio do game
void validateTest(char c){
  int error = 0;
  lcd.begin(0,2);
  for(int i = 0; i < strlen(wd); i++){
    if(wd[i] == letra[count]){
      filter[i] = wd[i];
    }else
    error++;
  }
  if(error  == strlen(wd)){
    loser--;
    if(loser == 0){
      lcd.print("Voce perdeu!");
      //TODO: CHAMAR A FUNÇÃO QUE REALIZARA UMA AÇÃO INDICANDO O GAMER OVER NOS LEDS
      count =0;
    }else{
      lcd.print(filter);
      lcd.setCursor(0,1);
      lcd.print("Ops! Errado");
      //TODO: CHAMAR A FUNÇÃO QUE REALIZARA UMA AÇÃO INDICANDO A PERCA DE UMA CHANCE NOS LEDS
      count =0;
    }

  }else{
    int charactere = 0;
    lcd.print(filter);
    for(int i=0; i < strlen(filter); i++){
      if(filter[i] != '_')
      charactere++;
    }
    if(charactere == strlen(filter)){
      lcd.blink();
      lcd.setCursor(0,1);
      lcd.print("###Parabens!!###");
    }else{
      lcd.setCursor(0,1);
      lcd.print("Esta correto!!");
    }
    count =0;
  }

}
