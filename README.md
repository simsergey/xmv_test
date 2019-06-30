# EN:
The application is designed to compare the performance of the vectors calculated in floating point numbers for one stream processed directly (FLOAT) or using SSE (XMVECTOR) for CPUs from different vendors and generations.

# RU:
Приложение предназначено для сравнения производительности вычислений векторов в числах с плавающей запятой для одного потока, проводимых непосредственно (FLOAT) либо с помощью SSE (XMVECTOR) на ЦП разных производителей и поколений.

Приложение получает разрешение высокоточного таймера в системе и проводит измерения для каждого этапа в тиках этого таймера, затем производится определение времени в наносекундах и определение производительности в мегафлопсах.

Предполагается 3 этапа - 2D, 3D, 4D векторы.

Исходный код может быть использован по лицензии MIT.
	
Автор: Соломаха С.С. - sergey.solomakha (a) yahoo.com
