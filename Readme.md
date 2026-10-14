# Diseño y construcción de una incubadora neonatal a escala


**Docente:** Erick Javier Argüello Prada

> **Nota de autoría:** la construcción física del modelo a escala (carcasa, base y cúpula) fue realizada. El circuito electrónico de control de temperatura y medición de peso no llegó a implementarse físicamente por parte del equipo; este informe documenta el diseño, los cálculos y el código que se habrían utilizado para completar esas dos funciones, de modo que la lógica completa del sistema quede documentada para el repositorio del laboratorío.

## 1. Introducción

Una incubadora neonatal debe mantener un ambiente térmico controlado (36°C–37,5°C) y permitir el monitoreo del peso del neonato. Este documento describe el diseño completo del sistema: identificación de partes, circuito de control de temperatura en lazo cerrado, sistema de medición de peso, y la construcción física del modelo a escala.

Además de su función clínica, el diseño de una incubadora neonatal representa una aplicación práctica de los principios de la instrumentación biomédica, la electrónica y los sistemas de control. La integración de sensores, circuitos de acondicionamiento de señal y dispositivos de visualización permite comprender cómo las variables físicas pueden convertirse en información útil para el monitoreo. En esta práctica, la construcción del modelo a escala y el diseño teórico de los sistemas de control de temperatura y medición de peso permiten relacionar los conceptos estudiados en el laboratorio con las necesidades de los equipos médicos reales. Asimismo, la identificación de las limitaciones del prototipo permite reconocer la importancia de la calibración, la validación experimental y las medidas de seguridad necesarias antes de considerar cualquier dispositivo para una aplicación clínica.

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

<img width="1024" height="1024" alt="LCD-I2c-1024x1024" src="https://github.com/user-attachments/assets/3072154f-af93-4592-bb35-2c885d8cfcf2" />

**Acondicionamiento:** la señal diferencial del puente (del orden de mV) se amplifica con un amplificador de instrumentación basado en LM741 (ganancia ajustable según el rango de peso del neonato, típicamente 1–5 kg) antes de entrar al conversor análogo-digital.

El circuito de medición de peso utiliza una celda de carga que transforma la fuerza aplicada en una señal eléctrica. Esta señal se amplifica y procesa para obtener el peso, que se mostraría en una pantalla LCD. Su precisión dependería de una calibración con masas conocidas.


## 3. Parte B — Construcción del modelo a escala

### 3.1 Descripción física (realizada)

- **Base/estructura:** madera reciclada (melamina), ensamblada en forma de cajón sobre 4 patas de madera con ruedas giratorias (tipo patas de silla), para dar movilidad al modelo.
- **Compartimento del circuito:** cajón interno en la base, diseñado para alojar la electrónica (hueco/cajón bajo la tapa superior, ver plano "Tabla 1/2/3").
- **Cúpula:** realizada en papel acetato transparente sobre un armazón de palitos de balso, simulando la cubierta transparente donde se ubicaría el neonato — versión artesanal del concepto de cúpula de acrílico planteado originalmente.
- **Rejillas:** diseñadas rejillas de acceso para manos (laterales) y una rejilla superior, según el boceto de planeación.

### 3.2 Materiales utilizados (realmente comprados/usados)

| Material | Origen |
|---|---|
| Tableros de melamina (3 piezas, medidas ~48×24cm y 44×20cm) | Reciclado/comprado |
| Patas de madera | Compradas |
| Ruedas giratorias tipo pata de silla (4) | Compradas |
| Papel acetato | Comprado |
| Palitos de balso | Comprados |
| Puntillas/grapas para ensamble | Compradas |

### 3.3 Costos estimados

*(completar con los valores reales de compra — placeholder para la tabla final del informe)*

| Ítem | Costo estimado |
|---|---|
| Estructura de madera + ruedas | $ |
| Acetato + balso (cúpula) | $ |
| Componentes electrónicos (no implementados) | $ |
| **Total estimado** | $ |

### 3.4 Comparación con sistemas comerciales

Sistemas comerciales como los de **Dräger**, **Instrumentalia S.A.S.** y **LEEX Medical** ofrecen control de temperatura de alta precisión (±0,1–0,2°C), alarmas redundantes, monitoreo de humedad y peso integrado, y certificaciones médicas (IEC 60601). El prototipo desarrollado en esta práctica tiene fines exclusivamente educativos: no cuenta con las certificaciones, redundancias de seguridad, ni la precisión de un dispositivo médico real, pero permite comprender los principios de control y acondicionamiento de señales involucrados.


## 4. Análisis de resultados

Dado que el circuito no se implementó físicamente, el análisis se basa en los valores de diseño calculados:
- El sistema de control de temperatura fue diseñado para mantener el rango 36°C–37,5°C mediante una ventana comparadora con holgura de ±4,8V tras la amplificación, lo que da margen suficiente ante ruido eléctrico.
- El sistema de peso reutiliza una metodología de calibración ya validada en la práctica de celda de carga del curso de Modelos de Sistemas Biológicos, por lo que se espera una linealidad similar (error esperado <5% con calibración de 3 puntos).
- No fue posible contrastar estos valores con mediciones reales ni con un patrón de peso conocido, dado que el circuito no se ensambló.




**Calibración:** se realiza con al menos 3 pesos patrón conocidos, ajustando PENDIENTE y OFFSET por regresión lineal (igual metodología usada en la práctica de celda de carga del curso de Modelos de Sistemas Biológicos).

 ## 5. Conclusiones

La práctica permitió desarrollar un modelo a escala de una incubadora neonatal, integrando la construcción de una estructura con cúpula transparente y una base independiente destinada a alojar los componentes electrónicos. El diseño contempló un sistema de control de temperatura mediante un termistor y comparadores, así como un sistema de medición de peso basado en una celda de carga. Sin embargo, aunque la estructura física se construyó satisfactoriamente, los circuitos electrónicos no llegaron a implementarse, por lo que no fue posible comprobar experimentalmente la precisión del control de temperatura ni la medición del peso. Esto evidencia la importancia de integrar y validar los sistemas electrónicos para verificar el funcionamiento esperado del prototipo. Como siguiente paso, se propone implementar los circuitos diseñados, realizar pruebas de temperatura y calibrar la celda de carga con masas conocidas, con el fin de evaluar el desempeño del sistema e identificar posibles mejoras en su funcionamiento y confiabilidad.

---

## 6. Preguntas para la discusión

*1. ¿Qué otras variables (y por qué) además de las aquí mencionadas son críticas en el monitoreo neonatal?*

La humedad relativa (afecta la pérdida de calor por evaporación en piel inmadura), la saturación de oxígeno (SpO₂), y el nivel de ruido/luz dentro de la incubadora (afectan el desarrollo neurológico del prematuro).

*2. ¿Qué haría falta para convertir el sistema desarrollado en una incubadora neonatal real?*

Certificación médica (IEC 60601-2-19), sensores redundantes y de grado médico, alarmas audibles/visuales ante fallas, control de humedad, filtrado HEPA del aire, materiales biocompatibles y pruebas de seguridad eléctrica.

*3. ¿Qué semejanzas hay entre una incubadora neonatal y una servo-cuna?*

Ambas regulan la temperatura del neonato mediante retroalimentación con un sensor de temperatura, pero la servo-cuna generalmente calienta por contacto/radiación (lámpara radiante abierta) mientras que la incubadora lo hace por convección en un ambiente cerrado.

---

