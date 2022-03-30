#include <lcom/lcf.h>
#include <lcom/timer.h>
#include <stdint.h>
#include "i8254.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {

if (freq > TIMER_FREQ || freq < 19 ) {
  printf("Frequency out of range!" );
  return 1; 
}
uint8_t status = 0;

if(timer_get_conf(timer, &status) != 0){ //significa que deu merda
  return 1;
}

int realtimer= TIMER_0+timer;
  uint8_t controlword=0;
  switch (timer)
  {
  case 0:
    controlword |= TIMER_SEL0;
    break;
  case 1:
    controlword |= TIMER_SEL1;
    break;
  case 2:
   controlword |= TIMER_SEL2;
    break;
  }

  controlword |= TIMER_LSB_MSB; //Ativa os bits 4 e 5 
  controlword |= (status & (0x0F)); //ativa os 4 bits menos significativos
  if(sys_outb(TIMER_CTRL,controlword)!=0)  //coloca a informação no registo de controlo
    return 1;

  uint16_t newfreq=(uint16_t)(TIMER_FREQ/freq);  // Calcula a nova frequencia, 
                                                //Tá em 16 bits por causa das funçoes abaixo
  uint8_t lsb,msb;
  if(util_get_LSB(newfreq ,&lsb)!=0)
    return 1;
  if(util_get_MSB(newfreq, &msb)!=0)
    return 1;

  if(sys_outb(realtimer,lsb)!=0) //altera o LSByte do timer que queremos
    return 1;
  if(sys_outb(realtimer,msb)!=0) //altera o MSByte do timer que queremos
    return 1;

  return 0;
}



  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
    /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_unsubscribe_int)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

void (timer_int_handler)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  uint8_t cmd = 0x0; // inicializar tudo a 0s

  /* To be implemented by the students */

   cmd |= (TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer));

    sys_outb(TIMER_CTRL, cmd); // para obter dados passamos a informacao do test á porta 0x43 = timer ctrl
    util_sys_inb(TIMER_0+timer, st); //para enviar informacao ao timer que queremos, timer0 + timer dá para selecionar entre 0,1,2
    // passamos um st tambem que é a informaçao para colocar 

  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {

union timer_status_field_val u;  //variavel que falta em timer_print_config

if(field == tsf_all){
  u.byte = st; // mostra a configuraçao toda

} else if(field == tsf_initial){ // inicialization mode LSB ou MSB 
  u.in_mode = st; 
  u.in_mode = (st & 0x30) >> 4;

    if(st & TIMER_LSB == 0 & TIMER_MSB == 0){
      u.in_mode = INVAL_val;
    } else if(st & TIMER_LSB == 0 & TIMER_MSB == 1){
      u.in_mode = MSB_only;
    } else if(st & TIMER_LSB == 1 & TIMER_MSB == 0 ){
      u.in_mode = LSB_only;
    } else {
      u.in_mode = MSB_after_LSB; 
    }


} else if(field == tsf_mode){
  u.count_mode = st;
  u.count_mode = (st & 0x0E) >> 1;
  
  buf = (st & (BIT(1) | BIT(2) | BIT(3))) >> 1; //  0000xxx1 = 0000xxx  

  if(st & buf == 0){
    u.count_mode = 0; 
  }

  switch(buf){
    case 0: 
      u.count_mode = 0; 
      break; 
    case 1: 
      u.count_mode = 1;
      break;
    case 2: 
      u.count_mode = 2; 
      break; 
    case 3: 
      u.count_mode = 3;
      break;
    case 4: 
      u.count_mode = 4; 
      break; 
    case 5: 
      u.count_mode = 5;
      break; 
      default: 
      return 1;
      break;

  }

}else{ // field == tsf_base
  u.bcd = st;

    if(st & TIMER_BCD == 0){
      u.bcd = false;
    }else {
      u.bcd = true;
    }
}

return timer_print_config(timer, field, u);
  
}
