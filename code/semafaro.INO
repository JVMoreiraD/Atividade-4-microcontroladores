const byte LED_VERMELHO = 33;
const byte LED_AMARELO = 32;
const byte LED_VERDE = 25;

const byte BOTAO = 12;

const byte LED_A = 22;
const byte LED_B = 23;
const byte LED_C = 2;
const byte LED_D = 4;
const byte LED_E = 5;
const byte LED_F = 21;
const byte LED_G = 19;

byte segmentos[] = {22, 23, 2, 4, 5, 21, 19};

const byte contagem = 9;

volatile bool iniciaContagem = false;

void IRAM_ATTR aoPressionarBotao()
{
    iniciaContagem = true;
}

const byte bits_por_numero[contagem] = {
    // GFEDCBA
    B0000110, // 1
    B1011011, // 2
    B1001111, // 3
    B1100110, // 4
    B1101101, // 5
    B1111101, // 6
    B0000111, // 7
    B1111111, // 8
    B1101111, // 9
};

void setup()
{
    pinMode(LED_VERMELHO, OUTPUT);
    pinMode(LED_AMARELO, OUTPUT);
    pinMode(LED_VERDE, OUTPUT);
    pinMode(segmentos[0], OUTPUT);
    pinMode(segmentos[1], OUTPUT);
    pinMode(segmentos[2], OUTPUT);
    pinMode(segmentos[3], OUTPUT);
    pinMode(segmentos[4], OUTPUT);
    pinMode(segmentos[5], OUTPUT);
    pinMode(segmentos[6], OUTPUT);
    pinMode(BOTAO, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(BOTAO), aoPressionarBotao, FALLING);
}

void loop()
{
    digitalWrite(LED_VERDE, HIGH);
    delay(1000);
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, HIGH);
    delay(1000);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERMELHO, HIGH);

    if (iniciaContagem)
    {
        for (int i = 0; i < contagem; i++)
        {
            acendeLeds(bits_por_numero[(contagem - 1) - i]);
            delay(1000);
        }
        apagaLeds();
        iniciaContagem = false;
    }

    delay(1000);
    digitalWrite(LED_VERMELHO, LOW);
}

void acendeLeds(byte bits_por_numero)
{
    for (int i = 0; i < 8; i++)
        digitalWrite(segmentos[i], bitRead(bits_por_numero, i));
}

void apagaLeds()
{
    const byte segmentoApagado = B0000000;

    for (int i = 0; i < 8; i++)
        digitalWrite(segmentos[i], bitRead(segmentoApagado, i));
}
