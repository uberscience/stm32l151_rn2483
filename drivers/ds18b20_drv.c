#include "ds18b20_drv.h"

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
    one_wire_drv_reset();//OWI_DetectPresence(bus);
    OWI_MatchRom(id);
    one_wire_drv_send_byte(DS18B20_CONVERT_T);//OWI_SendByte(DS18B20_CONVERT_T ,bus);

    /*ждем, когда датчик завершит преобразование*/
    delay_ms(300);//delay(1280000);//while (!one_wire_read_bit());//while (!OWI_ReadBit(bus));

    /*подаем сигнал сброса
    команду для адресации устройства на шине
    команду - чтение внутренней памяти
    затем считываем внутреннюю память датчика в массив
    */
    one_wire_drv_reset();//OWI_DetectPresence(bus);
    OWI_MatchRom(id);//OWI_MatchRom(id, bus);
    one_wire_drv_send_byte(DS18B20_READ_SCRATCHPAD);//OWI_SendByte(DS18B20_READ_SCRATCHPAD, bus);
    for (i = 0; i<=8; i++){
      scratchpad[i] = one_wire_drv_read_byte();
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
    one_wire_drv_send_byte(OWI_ROM_MATCH);//OWI_SendByte(OWI_ROM_MATCH, pin);
    // Do once for each byte.
    while (bytesLeft > 0)
    {
        // Transmit 1 byte of the ID to match.
    	one_wire_drv_send_byte(*romValue++);//OWI_SendByte(*romValue++, pin);
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
    one_wire_drv_send_byte(OWI_ROM_SEARCH);
    //OWI_SendByte(OWI_ROM_SEARCH, pin);
    // Walk through all 64 bits.
    while (currentBit <= 64)
    {
        bitA = one_wire_drv_read_bit();
        bitB = one_wire_drv_read_bit();
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
            one_wire_drv_send_bit(0x01);
            //OWI_WriteBit1(pin);
        }
        else
        {
        	one_wire_drv_send_bit(0x00);
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

      if (one_wire_drv_reset() == ONE_WIRE_DEV_NOT_FOUND){
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

void get_temp(unsigned int *t_val){

    unsigned int temperature = 0;
    unsigned char searchFlag = SEARCH_SENSORS;
    unsigned char crcFlag = 0;
    unsigned char num = 0;

        /*-флаг сброшен - выполнить поиск 1Wire устройств
    -если количество заданных устройсв совпадает с
    колличеством найденных - устанавливаем флаг,
    чтобы функция поиска больше не запускалась
    -отобразить количество найденных устройств*/
    if (searchFlag == SEARCH_SENSORS){
      num = 0;
      crcFlag = OWI_SearchDevices(allDevices, MAX_DEVICES, &num);

      if ((num == MAX_DEVICES)&&(crcFlag != SEARCH_CRC_ERROR)){
         searchFlag = SENSORS_FOUND;
      }
    }
    /*считать температуру первого найденного датчика
    если возвращена ошибка CRC, вывести строку "not"
    и сбросить флаг, чтобы функция поиска снова произвела
    опрос шины*/

    crcFlag = DS18B20_ReadTemperature(allDevices[0].id, &temperature);

    if (crcFlag != READ_CRC_ERROR){

       t_val[0] = temperature;
        //DS18B20_PrintTemperature(temperature);

    }
    else{
      //LCD_SendString("  not  ");
      t_val[0] = 0xFFFF;
      searchFlag = SEARCH_SENSORS;
    }

    /*считать температуру второго найденного датчика
    если возвращена ошибка CRC, вывести строку "not"
    и сбросить флаг, чтобы функция поиска снова произвела
    опрос шины*/

    crcFlag = DS18B20_ReadTemperature(allDevices[1].id, &temperature);

    if (crcFlag != READ_CRC_ERROR){
      t_val[1] = temperature;
      //DS18B20_PrintTemperature(temperature);

    }
    else{
      //LCD_SendString("  not  ");
      t_val[1] = 0xFFFF;
      searchFlag = SEARCH_SENSORS;
    }

    crcFlag = DS18B20_ReadTemperature(allDevices[2].id, &temperature);

    if (crcFlag != READ_CRC_ERROR){
      t_val[2] = temperature;
      //DS18B20_PrintTemperature(temperature);

    }
    else{
      //LCD_SendString("  not  ");
      t_val[2] = 0xFFFF;
      searchFlag = SEARCH_SENSORS;
    }

}
