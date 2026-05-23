# **Regresión Lineal y Descenso de Gradiente**

## **Introducción**
La regresión lineal es un método estadístico y de aprendizaje automático utilizado para modelar la relación entre una variable independiente ***x*** y una variable dependiente ***y***. Se ajusta una línea a los datos para predecir el valor de ***y*** a partir de ***x***, basada en la ecuación de la recta:

$$
y = \theta_0 + \theta_1 \cdot x
$$

Donde:
- $\theta_0$ es la intersección con el eje ***y*** (ordenada al origen).
- $\theta_1$ es la pendiente de la recta.

El objetivo es encontrar los valores de $\theta_0$ y $\theta_1$ que minimicen el error entre los valores predichos $\hat{y}$ y los valores reales ***y***.

## **Cálculo de la Regresión Lineal**

### **Definición del Modelo**
El modelo de regresión lineal busca minimizar el **error cuadrático medio (MSE)**:

$$
\text{MSE} = \frac{1}{n} \sum_{i=1}^n (y_i - \hat{y}_i)^2
$$

Donde:
- ***n*** es el número de datos.
- $y_i$ es el valor real.
- $\hat{y}_i$ = $\theta_0$ + $\theta_1$ $\cdot$ $x_i$ es el valor predicho.

### **Método de Descenso de Gradiente**
El **descenso de gradiente** es un algoritmo iterativo que ajusta los parámetros $\theta_0$ y $\theta_1$ para minimizar la función de pérdida (MSE). Se calcula mediante las siguientes fórmulas de actualización:

$$
\theta_0 = \theta_0 - \alpha \cdot \frac{\partial \text{MSE}}{\partial \theta_0}
$$

$$
\theta_1 = \theta_1 - \alpha \cdot \frac{\partial \text{MSE}}{\partial \theta_1}
$$

Las derivadas parciales son:

$$
\frac{\partial \text{MSE}}{\partial \theta_0} = \frac{1}{n} \sum_{i=1}^n (\hat{y}_i - y_i)
$$

$$
\frac{\partial \text{MSE}}{\partial \theta_1} = \frac{1}{n} \sum_{i=1}^n (\hat{y}_i - y_i) \cdot x_i
$$

Donde $\alpha$ es el **factor de aprendizaje**, que controla el tamaño de los pasos del algoritmo.

## **Cálculo de los Errores**
Las métricas de error son herramientas esenciales para evaluar la calidad de un modelo de regresión, como la regresión lineal. Estas métricas permiten medir cuán bien el modelo se ajusta a los datos reales, indicando la diferencia entre los valores predichos y los valores reales. Existen varias métricas que se utilizan para evaluar este tipo de modelos, y cada una tiene sus particularidades. Vamos a desglosar las métricas de error más comunes en el contexto de la regresión lineal.

### **Error Absoluto Medio (MAE):**
El Error Absoluto Medio (MAE, por sus siglas en inglés) mide el promedio de las diferencias absolutas entre los valores reales $y_i$ y los valores predichos 
$\hat{y}_i$

$$
\text{MAE} = \frac{1}{n} \sum_{i=1}^n |y_i - \hat{y}_i|
$$

Características:
- MAE es fácil de interpretar porque tiene las mismas unidades que la variable dependiente.
- Es sensible a todos los errores de manera similar, es decir, no penaliza los errores grandes más que los pequeños.
- No es tan útil cuando los errores grandes son muy importantes, ya que trata todos los errores de igual manera.

### **Error Cuadrático Medio (MSE):**
El Error Cuadrático Medio (MSE, por sus siglas en inglés) calcula el promedio de los errores elevados al cuadrado:

$$
\text{MSE} = \frac{1}{n} \sum_{i=1}^n (y_i - \hat{y}_i)^2
$$

Características:
- Al elevar al cuadrado las diferencias, el MSE penaliza más los errores grandes. Esto hace que sea útil cuando queremos que el modelo sea especialmente preciso y evitar grandes desviaciones.
- Sin embargo, esta penalización puede hacer que el MSE sea sensible a los outliers (valores atípicos), lo que puede ser un inconveniente si los outliers no son representativos de los datos en general.

### **Raíz del Error Cuadrático Medio (RMSE):**
El RMSE es simplemente la raíz cuadrada del MSE y se utiliza para devolver el error a las mismas unidades que los valores de ***y***, haciendo que su interpretación sea más intuitiva:

$$
\text{RMSE} = \sqrt{\text{MSE}}
$$

Características:
- Al igual que el MSE, el RMSE penaliza los errores grandes, pero tiene la ventaja de que sus unidades son las mismas que las de los datos originales, lo que facilita su interpretación.
- RMSE es más sensible a los outliers que MAE, debido a la amplificación de los errores grandes.

### **Coeficiente de Determinación ($R^2$):**
El coeficiente de determinación $R^2$ mide cuánto se ajustan los valores predichos a los datos reales. Se calcula como:

$$
R^2 = 1 - \frac{\sum_{i=1}^n(y_i - \hat{y_i})^2}{\sum_{i=1}^n(y_i - \bar{y})^2}
$$

Donde $\bar{y}$ es el valor promedio de ***y***.

Características:
- Un $R^2$ de 1 indica que el modelo explica el 100% de la varianza de los datos, es decir, que las predicciones son perfectas.
- Un $R^2$ de 0 indica que el modelo no tiene capacidad predictiva y es tan bueno como simplemente predecir el promedio de ***y*** para todos los casos.
- Los valores de $R^2$ pueden ser negativos si el modelo es peor que una simple predicción constante (como el valor medio).
- $R^2$ no está libre de limitaciones, ya que puede dar a engaño en algunos contextos, como en modelos que no son lineales o cuando se tienen demasiadas variables explicativas.

### Comparación entre las métricas de error
| Métrica       | Sensibilidad a los outliers | Interpretación        | Unidades     |
|---------------|-----------------------------|-----------------------|--------------|
| **MAE**       | Baja                        | Promedio de errores absolutos | Mismas que los datos |
| **MSE**       | Alta                        | Promedio de errores al cuadrado | Mismas que $y^2$   |
| **RMSE**      | Alta                        | Raíz cuadrada de MSE  | Mismas que los datos |
| **$R^2$**   | No                           | Proporción de la variabilidad de la variable dependiente que es explicada por el modelo | Ninguna (relativo)   |

### Elección de la métrica adecuada
- MAE es útil cuando quieres tratar los errores de manera igualitaria y no te importa si los errores grandes ocurren.
- MSE es más sensible a los errores grandes y es preferido cuando se desea penalizar los grandes errores.
- RMSE es útil cuando quieres penalizar errores grandes pero necesitas una interpretación más directa debido a su escala.
- $R^2$ es una métrica estándar para evaluar el ajuste de un modelo, pero no siempre es la mejor para modelos no lineales.

### Consideraciones adicionales
- Outliers: Si tienes datos con muchos valores atípicos, las métricas como MSE y RMSE pueden no ser ideales, ya que estos errores grandes influyen mucho en el resultado final. En ese caso, MAE podría ser más robusto.
- Dependencia del contexto: Es importante elegir la métrica adecuada en función del problema que se está resolviendo. Algunas métricas pueden ser más apropiadas dependiendo de la importancia de los errores grandes en tu caso específico.

## Predicción tras el aprendizaje
En el contexto de aprendizaje automático y modelos de regresión, es inusual que un modelo prediga el valor exacto para todos los puntos de datos, especialmente en datos no vistos o de prueba. Si un modelo predice valores que son exactamente iguales a los valores reales, esto podría ser una señal de sobreajuste (Overfitting).

### Overfitting
El Overfitting ocurre cuando un modelo no solo aprende los patrones subyacentes de los datos, sino que también aprende el ruido o las fluctuaciones aleatorias presentes en esos datos. Esto hace que el modelo sea excesivamente complejo y que, aunque funcione muy bien con los datos de entrenamiento, pierda capacidad para generalizar correctamente a datos nuevos o no vistos.

En el caso del Overfitting:
- El modelo tiene un rendimiento muy bueno en los datos de entrenamiento, incluso llegando a predecir los valores exactos.
- Sin embargo, tiene un rendimiento deficiente en los datos de prueba o en nuevos datos, porque el modelo ha "memorizado" los datos, no ha aprendido a generalizar.

### Por qué el Overfitting es sospechoso
Si un modelo predice exactamente los valores tanto en los datos de entrenamiento como en los de prueba, podría estar sufriendo de Overfitting. Esto sucede porque el modelo probablemente ha "memorizado" los puntos de datos (o el ruido), en lugar de aprender la verdadera relación entre las variables.

En la práctica, siempre se esperan pequeñas desviaciones entre los valores predichos y los valores reales, debido al ruido inherente en los datos del mundo real. Los modelos deberían aproximarse a la distribución subyacente de los datos, no memorizarla.

### Señales de Overfitting
1. Alta precisión en los datos de entrenamiento pero baja precisión en los datos de prueba.
2. Predicciones exactas o errores muy bajos (por ejemplo, MSE = 0 o MAE = 0) en los datos de entrenamiento, pero pobre desempeño en los datos de prueba.
3. El modelo se vuelve demasiado complejo con muchos parámetros o polinomios de alto grado, lo que lleva al sobreajuste.

### Cómo Corregir el Overfitting
Existen varias técnicas para corregir o mitigar el Overfitting:

1. Simplificar el modelo: Utiliza modelos más simples, con menos características o parámetros. Por ejemplo, evita polinomios de muy alto grado o modelos con demasiados parámetros, a menos que sea necesario.
2. Regularización: Técnicas de regularización como L1 (Lasso) o L2 (Ridge) pueden ser usadas para penalizar coeficientes grandes, evitando que el modelo se ajuste demasiado al ruido de los datos.
3. Validación cruzada: Usa validación cruzada (como la validación cruzada k-fold) para asegurar que el modelo generaliza bien a diferentes subconjuntos de los datos. Esto ayuda a detectar el sobreajuste a tiempo, probando el rendimiento del modelo en datos que no ha visto durante el entrenamiento.
4. Más datos: Si es posible, aumenta el tamaño del conjunto de entrenamiento. Tener más datos puede ayudar al modelo a generalizar mejor y reducir las posibilidades de sobreajuste.
5. Detención temprana (Early Stopping): En modelos iterativos como las redes neuronales, puedes detener el entrenamiento cuando el rendimiento del modelo en el conjunto de validación empieza a deteriorarse, incluso si sigue mejorando en los datos de entrenamiento.

### Ejemplo:
Supongamos que estás utilizando regresión lineal para hacer predicciones. Si el modelo es entrenado en un conjunto de datos pequeño y predice los valores exactos, esto podría ser una señal de Overfitting. Puedes corregir esto utilizando regularización (por ejemplo, regresión Ridge), que penaliza los coeficientes grandes y obliga al modelo a centrarse en patrones más generales en lugar de ajustar el ruido.

#### Ejemplo Visual de Overfiting:
Imagina que estás ajustando una línea de regresión a un conjunto de puntos de datos. Una regresión lineal simple podría ajustarse bien a los datos con una línea recta. Sin embargo, si ajustas un polinomio de alto grado, la curva podría ajustarse exactamente a los puntos de datos, pero sería muy sensible a pequeños cambios, especialmente si se introduce un nuevo dato. Este modelo excesivamente complejo podría tener un error pequeño en los datos de entrenamiento, pero tendría un mal desempeño con datos nuevos, lo que indica un Overfitting.

### Regularización

Las estrategias de regularización incorporan penalizaciones en el ajuste por mínimos cuadrados ordinarios (OLS) con el objetivo de evitar overfitting, reducir varianza, atenuar el efecto de la correlación entre predictores y minimizar la influencia en el modelo de los predictores menos relevantes. Por lo general, aplicando regularización se consigue modelos con mayor poder predictivo (generalización).

Dado que estos métodos de regularización actúan sobre la magnitud de los coeficientes del modelo, todos deben de estár en la misma escala, por esta razón es necesario estandarizar o normalizar los predictores antes de entrenar el modelo.

#### Ridge

La regularización Ridge penaliza la suma de los coeficientes elevados al cuadrado
			$$||\beta||_2^2 = \sum_{j=1}^{p} \beta_j^2$$

 A esta penalización se le conoce como l2 y tiene el efecto de reducir de forma proporcional el valor de todos los coeficientes del modelo pero sin que estos lleguen a cero. El grado de penalización está controlado por el hiperparámetro  λ.
 
 Cuando  λ=0, la penalización es nula y el resultado es equivalente al de un modelo lineal por mínimos cuadrados ordinarios (OLS). A medida que  λ aumenta, mayor es la penalización y menor el valor de los predictores.

$$\sum_{i=1}^{n} \left( y_i - \beta_0 - \sum_{j=1}^{p} \beta_j x_{ij} \right)^2 + \lambda \sum_{j=1}^{p} \beta_j^2 = \text{suma de residuos cuadrados} + \lambda \sum_{j=1}^{p} \beta_j^2$$
 
La principal ventaja de aplicar ridge frente al ajuste por mínimos cuadrados ordinarios (OLS) es la reducción de varianza. Por lo general, en situaciones en las que la relación entre la variable respuesta y los predictores es aproximadamente lineal, las estimaciones por mínimos cuadrados tienen poco bias pero aún pueden sufrir alta varianza (pequeños cambios en los datos de entrenamiento tienen mucho impacto en el modelo resultante). Este problema se acentúa conforme el número de predictores introducido en el modelo se aproxima al número de observaciones de entrenamiento, llegando al punto en que, si  p>n, no es posible ajustar el modelo por mínimos cuadrados ordinarios. Empleando un valor adecuado de  λ, el método de ridge es capaz de reducir varianza sin apenas aumentar el bias, consiguiendo así un menor error total.

La desventaja del método ridge es que, el modelo final, incluye todos los predictores. Esto es así porque, si bien la penalización fuerza a que los coeficientes tiendan a cero, nunca llegan a ser exactamente cero (solo si  λ=∞). Este método consigue minimizar la influencia sobre el modelo de los predictores menos relacionados con la variable respuesta pero, en el modelo final, van a seguir apareciendo. Aunque esto no supone un problema para la precisión del modelo, sí lo es para su interpretación.

#### Lasso

La regularización Lasso penaliza la suma del valor absolutos de los coeficientes de regresión
			$$||\beta||_1 = \sum_{j=1}^{p} |\beta_j|$$

A esta penalización se le conoce como l1 y tiene el efecto de forzar a que los coeficientes de los predictores tiendan a cero. Dado que un predictor con coeficiente de regresión cero no influye en el modelo, lasso consigue excluir los predictores menos relevantes. Al igual que en ridge, el grado de penalización está controlado por el hiperparámetro  λ. Cuando  λ=0, el resultado es equivalente al de un modelo lineal por mínimos cuadrados ordinarios. A medida que  λ aumenta, mayor es la penalización y más predictores quedan excluidos.

$$\sum_{i=1}^{n} \left( y_i - \beta_0 - \sum_{j=1}^{p} \beta_j x_{ij} \right)^2 + \lambda \sum_{j=1}^{p} |\beta_j| = \text{suma de residuos cuadrados} + \lambda \sum_{j=1}^{p} |\beta_j|$$

 
#### Comparación Ridge y Lasso

La principal diferencia práctica entre lasso y ridge es que el primero consigue que algunos coeficientes sean exactamente cero, por lo que realiza selección de predictores, mientras que el segundo no llega a excluir ninguno. Esto supone una ventaja notable de lasso en escenarios donde no todos los predictores son importantes para el modelo y se desea que los menos influyentes queden excluidos.

Por otro lado, cuando existen predictores altamente correlacionados (linealmente), ridge reduce la influencia de todos ellos a la vez y de forma proporcional, mientras que lasso tiende a seleccionar uno de ellos, dándole todo el peso y excluyendo al resto. En presencia de correlaciones, esta selección varía mucho con pequeñas perturbaciones (cambios en los datos de entrenamiento), por lo que, las soluciones de lasso, son muy inestables si los predictores están altamente correlacionados.

Para conseguir un equilibrio óptimo entre estas dos propiedades, se puede emplear lo que se conoce como penalización elastic net, que combina ambas estrategias.

#### Elastic net

Elastic net incluye una regularización que combina la penalización l1 y l2  $$\alpha \lambda ||\beta||_1 + \frac{1}{2} (1 - \alpha) ||\beta||_2^2$$

El grado en que influye cada una de las penalizaciones está controlado por el hiperparámetro  α

Su valor está comprendido en el intervalo [0,1]. Cuando  α=0, se aplica ridge y cuando  α=1 se aplica Lasso. La combinación de ambas penalizaciones suele dar lugar a buenos resultados. Una estrategia frecuentemente utilizada es asignarle casi todo el peso a la penalización l1 ( α muy próximo a 1) para conseguir seleccionar predictores y un poco a la l2 para dar cierta estabilidad en el caso de que algunos predictores estén correlacionados.

$$\frac{\sum_{i=1}^{n} \left( y_i - \beta_0 - \sum_{j=1}^{p} \beta_j x_{ij} \right)^2}{2n} + \lambda \left( \alpha \sum_{j=1}^{p} |\beta_j| + \frac{1-\alpha}{2} \sum_{j=1}^{p} \beta_j^2 \right)$$

Se emplee un método u otro <u>siempre hay que estandarizar o normalizar los predictores</u>.

Aunque el valor óptimo de  λ es aquel con el que se minimiza el error de validación cruzada, una práctica extendida es utilizar, en lugar de este, el mayor valor de  λ que se aleja menos de una desviación típica del óptimo. De este modo, se consigue un modelo más sencillo (excluye más predictores) pero cuya capacidad predictiva es similar a la conseguida con el modelo más complejo.

### Conclusión
- El Overfitting ocurre cuando el modelo se vuelve demasiado complejo y se ajusta demasiado a los datos de entrenamiento, capturando el ruido en lugar de los patrones reales.
- Si un modelo predice valores exactos, podría estar sufriendo deOverfitting, especialmente si el rendimiento en los datos de prueba es malo.
- Regularización, simplificación del modelo y validación cruzada son algunas de las técnicas utilizadas para mitigar el Overfitting.

## **Referencias**
1. Documentación oficial de Python: [https://docs.python.org/3/](https://docs.python.org/3/)
2. Artículo sobre regresión lineal de Towards Data Science: [Linear Regression](https://towardsdatascience.com/linear-regression-detailed-view-ea73175f6e86)
3. Curso interactivo gratuito de Machine Learning de Google: [Google Machine Learning Crash Course](https://developers.google.com/machine-learning/crash-course)
4. Libro: *Introduction to Statistical Learning* - James, Witten, Hastie, Tibshirani.
5. ¿Qué es el sobreajuste?: En castellano https://www.ibm.com/es-es/topics/overfitting?mhsrc=ibmsearch_a&mhq=overfitting y en inglés:
https://www.ibm.com/topics/overfitting?mhsrc=ibmsearch_a&mhq=overfitting
6. What Is Overfitting In Machine Learning: https://robots.net/fintech/what-is-overfitting-in-machine-learning/
7. Regularización del Overfitting: https://cienciadedatos.net/documentos/py14-ridge-lasso-elastic-net-python