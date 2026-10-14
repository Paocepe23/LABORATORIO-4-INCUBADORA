# Diseño y construcción de una incubadora neonatal a escala


**Docente:** Erick Javier Argüello Prada

> **Nota de autoría:** la construcción física del modelo a escala (carcasa, base y cúpula) fue realizada. El circuito electrónico de control de temperatura y medición de peso no llegó a implementarse físicamente por parte del equipo; este informe documenta el diseño, los cálculos y el código que se habrían utilizado para completar esas dos funciones, de modo que la lógica completa del sistema quede documentada para el repositorio del laboratorío---

## 1. Introducción

Una incubadora neonatal debe mantener un ambiente térmico controlado (36°C–37,5°C) y permitir el monitoreo del peso del neonato. Este documento describe el diseño completo del sistema: identificación de partes, circuito de control de temperatura en lazo cerrado, sistema de medición de peso, y la construcción física del modelo a escala.

---

## 2. Parte A — Diseño y simulación

### 2.1 Partes principales de una incubadora neonatal

| Parte | Función |
|---|---|
| Cúpula/cubierta | Aísla térmicamente y permite visibilidad hacia el neonato |
| Sistema de calefacción (resistencia + ventilador) | Calienta el aire por convección hasta el rango objetivo |
| Sensor de temperatura (termistor) | Mide la temperatura del aire interior |
| Sistema de control | Compara la temperatura medida contra el rango deseado y activa/desactiva la calefacción |
| Sensor de peso (galga/celda de carga) | Estima el peso del neonato |
| Indicadores (LEDs, display) | Comunican el estado del sistema |

### 2.2 Circuito de control de temperatura (lazo cerrado)

**Esquema de bloques:** Termistor (divisor de voltaje) → Amplificador diferencial LM741 → Ventana comparadora (2× LM741) → LEDs + actuador

**Sensado:** termistor NTC 10kΩ B3950 en divisor de voltaje (Vcc=5V, R_fija=6,2kΩ):
- A 36°C → V ≈ 2,49 V
- A 37,5°C → V ≈ 2,57 V

**Amplificación (diferencial, resta el punto medio y amplifica la diferencia):**
Vout = (R2/R1)·(V_sensor − V_ref), con R1=R3=1kΩ, R2=R4=120kΩ, V_ref=2,53V (punto medio, ajustado con trimmer 10kΩ multivuelta)
- Ganancia efectiva: 120
- Vout(36°C) ≈ −4,8V | Vout(37,5°C) ≈ +4,8V

**Ventana comparadora (2× LM741 en lazo abierto):**
- Comparador alto: dispara si Vout > +4,8V → temperatura por encima de 37,5°C
- Comparador bajo: dispara si Vout < −4,8V → temperatura por debajo de 36°C

**Indicación LED — esquema de colores de este proyecto (variación respecto a la guía base):**

| LED | Color | Condición |
|---|---|---|
| Rango correcto | 🟢 Verde | 36°C ≤ T ≤ 37,5°C (ambos comparadores en bajo → lógica NOR) |
| Muy frío | 🔵 Azul | T < 36°C (activa también el actuador de calefacción) |
| Muy caliente | 🔴 Rojo | T > 37,5°C |

**Actuador:** el comparador bajo (frío) activa un transistor NPN 2N2222 (R_base ≈ 1kΩ) que enciende el relé/transistor de potencia del calefactor + ventilador. Diodo 1N4007 en antiparalelo sobre el ventilador como protección contra picos inductivos.



### 2.3 Circuito de medición de peso

**Sensor:** celda de carga (galga extensométrica) en configuración de puente de Wheatstone.

**Esquema de bloques:** Celda de carga (puente de Wheatstone) → Amplificador de instrumentación (LM741) → Microcontrolador (ADC) → Display LCD 16×2

**Acondicionamiento:** la señal diferencial del puente (del orden de mV) se amplifica con un amplificador de instrumentación basado en LM741 (ganancia ajustable según el rango de peso del neonato, típicamente 1–5 kg) antes de entrar al conversor análogo-digital.




**Calibración:** se realiza con al menos 3 pesos patrón conocidos, ajustando PENDIENTE y OFFSET por regresión lineal (igual metodología usada en la práctica de celda de carga del curso de Modelos de Sistemas Biológicos).


