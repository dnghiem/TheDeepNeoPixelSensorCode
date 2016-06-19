void pirRead() {

  unsigned long current_pir_read = millis();
  
  if ((unsigned long)(current_pir_read - prev_pir_read) >= pir_read_interval) {
      prev_pir_read = millis();

      pirstatus = digitalRead(PIRpin); 

  }
  
}

