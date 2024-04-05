

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>



void initADC(void);

int conteo = 0;

int main(void)
{
	cli();
	DDRC |= 0xFF
	PORTC = 0;
	DDRD |= 0xFF
	PORTD = 0;
	UCSR0B = 0;
	PORTB = 0b00000011;		//Pull Up en PB0 y PB1
	initADC();
	sei(); 
	
	
	
    while(1)
    {
	ADCSRA |= (1<<ADSC);
	_delay_ms(200);	
    }
}

void initADC(void){
	ADMUX = 0;
	//referencia AVVC = 5V
	ADMUX |= (1<<REFS0);
	ADMUX &= ~(1<<REFS1);
	
	//Justificaci�n a la izquierda
	ADMUX |= (1<<ADLAR);
	ADCSRA = 0;

	//Habilitando la interrupci�n del ADC
	ADCSRA |= (1<<ADIE);
	
	//Habilitar prescaler de 16M7128 Fadc = 125kHz
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	
	// Habilitando el ADC 
	ADCSRA |= (1<<ADEN);	
		
}

ISR(ADC_vect){
	
	PORTD = ADCH;
	ADCSRA |= (1<<ADIF);
	
}

ISR(PCINT0_vect){
	
	
	if(((PINB) & (1<<0)) == 0){
		conteo ++;
		if(conteo >= 255){
			conteo = 255;
		}
		PORTD = conteo;
	}
	
	if(((PINB) & (1<<1)) == 0){
		conteo --;
		if(conteo <= 0){
			conteo = 0;
		}
		PORTD = conteo;
	}
	
	
	
}