#include "onewire.h"
//#include "RN2483.h"

void delay(uint32_t delay){
	while(delay--);
}

void one_wire_init(void){
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_AHBPeriphClockCmd(ONE_WIRE_RCC, ENABLE); 
    RCC_AHBPeriphClockCmd(ONE_WIRE_VDD_RCC, ENABLE); 
    
    GPIO_InitStructure.GPIO_Pin =  ONE_WIRE_DQ_PIN_TX;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(ONE_WIRE_DQ_PORT, &GPIO_InitStructure);   
    
    /*GPIO_InitStructure.GPIO_Pin   = ONE_WIRE_DQ_PIN_RX;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
    GPIO_Init(ONE_WIRE_DQ_PORT, &GPIO_InitStructure);*/
  
    GPIO_InitStructure.GPIO_Pin   = ONE_WIRE_VDD_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
    GPIO_Init(ONE_WIRE_VDD_PORT, &GPIO_InitStructure);
}


void send_presence(void){
    uint16_t i;
    ONE_WIRE_DQ_TX_HI;
    for (i = 0;i<128;i++);//~5us
	ONE_WIRE_DQ_TX_LO;
    for (i = 0;i<1500;i++);//~500 us
	ONE_WIRE_DQ_TX_HI;
}

uint8_t one_wire_reset(void){
    
    uint16_t i;
    send_presence();
    for( i = 0; i<400;i++){
        if(!(GPIO_ReadInputDataBit(ONE_WIRE_DQ_PORT, ONE_WIRE_DQ_PIN_RX))){
            while(!(GPIO_ReadInputDataBit(ONE_WIRE_DQ_PORT, ONE_WIRE_DQ_PIN_RX)));
            return ONE_WIRE_DEV_FOUND;
        }
    }
    return ONE_WIRE_DEV_NFOUND;
}

void one_wire_write_bit(uint8_t bit){
    uint8_t i;
	ONE_WIRE_DQ_TX_LO;
    if(bit > 0){
	for(i = 0; i < 20 ; i++);//~5us
	ONE_WIRE_DQ_TX_HI;
    for(i = 0; i<200; i++);//~65us
    }
    else {
	for(i = 0; i<200; i++);//~65us
    ONE_WIRE_DQ_TX_HI;
    for(i = 0; i < 20 ; i++);//~5us
    }
}

void one_wire_write_byte(uint8_t data) {
 uint8_t i;

  for (i = 8; i; i--) {
    one_wire_write_bit(data & 1);
    data >>= 1;
  }
}

uint8_t one_wire_read_bit(void){
    uint8_t bit,i;
    //for(i = 0; i<70; i++);//~65us
    ONE_WIRE_DQ_TX_LO;
    for(i = 0; i < 5 ; i++);//~5us
    ONE_WIRE_DQ_TX_HI;
    for(i = 0; i < 5 ; i++);//~5us
    bit = GPIO_ReadInputDataBit(ONE_WIRE_DQ_PORT, ONE_WIRE_DQ_PIN_RX);
    for(i = 0; i<50; i++);//~65us
    return bit;
}

uint8_t one_wire_read_byte(void){
  uint8_t byte = 0, i;
  for (i = 8; i; i--) {
    byte >>= 1;
    if (one_wire_read_bit() > 0)
      byte |= 0x80;
  }
  //for(i = 0; i<200; i++);//~65us
  return byte;
}

unsigned char OWI_CheckScratchPadCRC(unsigned char * scratchpad)
{
    unsigned char i;
    unsigned char crc8 = 0;
    
    for (i = 0; i < 8; i++)
    {
        crc8 = OWI_ComputeCRC8(*scratchpad, crc8);
        scratchpad++;
    }
    if (crc8 == (*scratchpad))
    {
        return OWI_CRC_OK;
    }
    return OWI_CRC_ERROR;
}

unsigned char DS18B20_ReadTemperature(unsigned char * id, unsigned int* temperature)
{
    unsigned char scratchpad[9];
    unsigned char i;
  
    /*подаем сигнал сброса
    команду для адресации устройства на шине
    подаем команду - запук преобразования */
    one_wire_reset();//OWI_DetectPresence(bus);
    OWI_MatchRom(id);
    one_wire_write_byte(DS18B20_CONVERT_T);//OWI_SendByte(DS18B20_CONVERT_T ,bus);

    /*ждем, когда датчик завершит преобразование*/ 
    delay(1280000);//while (!one_wire_read_bit());//while (!OWI_ReadBit(bus));

    /*подаем сигнал сброса
    команду для адресации устройства на шине
    команду - чтение внутренней памяти
    затем считываем внутреннюю память датчика в массив
    */
    one_wire_reset();//OWI_DetectPresence(bus);
    OWI_MatchRom(id);//OWI_MatchRom(id, bus);
    one_wire_write_byte(DS18B20_READ_SCRATCHPAD);//OWI_SendByte(DS18B20_READ_SCRATCHPAD, bus);
    for (i = 0; i<=8; i++){
      scratchpad[i] = one_wire_read_byte();
    }
    
    if(OWI_CheckScratchPadCRC(scratchpad) != OWI_CRC_OK){
      return READ_CRC_ERROR;
    }
    
    *temperature = (unsigned int)scratchpad[0];
    *temperature |= ((unsigned int)scratchpad[1] << 8);
    
    return READ_SUCCESSFUL;
}

void OWI_MatchRom(unsigned char * romValue)
{
    unsigned char bytesLeft = 8;   
    
    // Send the MATCH ROM command.
    one_wire_write_byte(OWI_ROM_MATCH);//OWI_SendByte(OWI_ROM_MATCH, pin);

    // Do once for each byte.
    while (bytesLeft > 0)
    {
        // Transmit 1 byte of the ID to match.
        one_wire_write_byte(*romValue++);//OWI_SendByte(*romValue++, pin);
        bytesLeft--;
    }
}

unsigned char OWI_SearchRom(unsigned char * bitPattern, unsigned char lastDeviation)
{
    unsigned char currentBit = 1;
    unsigned char newDeviation = 0;
    unsigned char bitMask = 0x01;
    unsigned char bitA;
    unsigned char bitB;

    // Send SEARCH ROM command on the bus.
    one_wire_write_byte(OWI_ROM_SEARCH);
    //OWI_SendByte(OWI_ROM_SEARCH, pin);
    
    // Walk through all 64 bits.
    while (currentBit <= 64)
    {   
        
        bitA = one_wire_read_bit();
        bitB = one_wire_read_bit();
        // Read bit from bus twice.
        //bitA = OWI_ReadBit(pin);
        //bitB = OWI_ReadBit(pin);

        if (bitA && bitB)
        {
            // Both bits 1 (Error).
            newDeviation = OWI_ROM_SEARCH_FAILED;
            return SEARCH_ERROR;
        }
        else if (bitA ^ bitB)
        {
            // Bits A and B are different. All devices have the same bit here.
            // Set the bit in bitPattern to this value.
            if (bitA)
            {
                (*bitPattern) |= bitMask;
            }
            else
            {
                (*bitPattern) &= ~bitMask;
            }
        }
        else // Both bits 0
        {
            // If this is where a choice was made the last time,
            // a '1' bit is selected this time.
            if (currentBit == lastDeviation)
            {
                (*bitPattern) |= bitMask;
            }
            // For the rest of the id, '0' bits are selected when
            // discrepancies occur.
            else if (currentBit > lastDeviation)
            {
                (*bitPattern) &= ~bitMask;
                newDeviation = currentBit;
            }
            // If current bit in bit pattern = 0, then this is
            // out new deviation.
            else if ( !(*bitPattern & bitMask)) 
            {
                newDeviation = currentBit;
            }
            // IF the bit is already 1, do nothing.
            else
            {
            
            }
        }
                
        
        // Send the selected bit to the bus.
        if ((*bitPattern) & bitMask)
        {
            one_wire_write_bit(0x01);
            //OWI_WriteBit1(pin);
        }
        else
        {
            one_wire_write_bit(0x00);
            //OWI_WriteBit0(pin);
        }

        // Increment current bit.    
        currentBit++;

        // Adjust bitMask and bitPattern pointer.    
        bitMask <<= 1;
        if (!bitMask)
        {
            bitMask = 0x01;
            bitPattern++;
        }
    }
    return newDeviation;
}

unsigned char OWI_ComputeCRC8(unsigned char inData, unsigned char seed)
{
    unsigned char bitsLeft;
    unsigned char temp;

    for (bitsLeft = 8; bitsLeft > 0; bitsLeft--)
    {
        temp = ((seed ^ inData) & 0x01);
        if (temp == 0)
        {
            seed >>= 1;
        }
        else
        {
            seed ^= 0x18;
            seed >>= 1;
            seed |= 0x80;
        }
        inData >>= 1;
    }
    return seed;    
}

unsigned char OWI_CheckRomCRC(unsigned char * romValue)
{
    unsigned char i;
    unsigned char crc8 = 0;
    
    for (i = 0; i < 7; i++)
    {
        crc8 = OWI_ComputeCRC8(*romValue, crc8);
        romValue++;
    }
    if (crc8 == (*romValue))
    {
        return OWI_CRC_OK;
    }
    return OWI_CRC_ERROR;
}

unsigned char OWI_SearchDevices(OWI_device * devices, unsigned char numDevices, unsigned char *num)
{
    unsigned char i, j;
    unsigned char * newID;
    unsigned char * currentID;
    unsigned char lastDeviation;
    unsigned char numFoundDevices;
    unsigned char flag = SEARCH_SUCCESSFUL;
    
    //сбрасываем адреса 1Wire устройств    
    for (i = 0; i < numDevices; i++)
    {
        for (j = 0; j < 8; j++)
        {
            devices[i].id[j] = 0x00;
        }
    }
    
    numFoundDevices = 0;
    newID = devices[0].id;
    lastDeviation = 0;
    currentID = newID;

    do  
    {
      memcpy(newID, currentID, 8);
      if (one_wire_reset() == ONE_WIRE_DEV_NFOUND){
        return SEARCH_ERROR;        
      };
      lastDeviation = OWI_SearchRom(newID, lastDeviation);
      currentID = newID;
      numFoundDevices++;
      newID=devices[numFoundDevices].id;                
    } while(lastDeviation != OWI_ROM_SEARCH_FINISHED);            

    
    // Go through all the devices and do CRC check.
    for (i = 0; i < numFoundDevices; i++)
    {
        // If any id has a crc error, return error.
        if(OWI_CheckRomCRC(devices[i].id) != OWI_CRC_OK)
        {
            flag = SEARCH_CRC_ERROR;
        }
        else 
        {
           (*num)++;
        }
    }
    // Else, return Successful.
    return flag;
}

