#include <lcom/lcf.h>

#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (util_sys_inb)(int port, uint8_t *value) {
  /* To be implemented by the students */
  uint32_t num32 = 0x00;
  if (util_sys_inb(port, &num32) != 0) return 1;
  value = (uint8_t) num32;


  return 0;
}
