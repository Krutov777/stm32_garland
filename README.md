![](https://github.com/Krutov777/stm32_garland/blob/main/PVPKR_4936_ru.pdf)

## EN:

### [Documention on EN](https://github.com/Krutov777/stm32_garland/blob/main/PVPKR_4936_en.pdf)

### Use case diagramm:

<img src="https://raw.githubusercontent.com/Krutov777/stm32_garland/main/use_case_diagramm_EN.jpg" data-canonical-src="https://raw.githubusercontent.com/Krutov777/stm32_garland/main/use_case_diagramm_EN.jpg" width="361" height="492" /> 
        
Within the framework of the garland model being developed, the following performers (actors) are distinguished:
– User;
– LEDs;
– Microcontroller (as a control device).
            
The main functions of the garland:
An LED (two LEDs) moves along the garland in one direction or the other.
The garland has 3 buttons to change the operating mode:   
  1)Changing the speed of the LEDs (4 speeds – ignition and extinguishing 1c, 0.5, 0.25, 0.04)    
  2)Changing the direction of movement (clockwise and counterclockwise)   
  3)Changing the mode (1 or 2 lights)   
Restrictions:
Pressing multiple buttons will be ignored
A PWM signal is used for smooth ignition and attenuation

## RU:

### [Документация на русском](https://github.com/Krutov777/stm32_garland/blob/main/PVPKR_4936_ru.pdf)

### Диаграмма вариантов использования:

![use case diagramm](https://raw.githubusercontent.com/Krutov777/stm32_garland/main/use_case_diagramm.jpg)

В рамках разрабатываемой модели гирлянды выделяются следующие исполнители (актеры):
– Пользователь;
– Светодиоды;
– Микроконтроллер (как управляющее устройство).

Основные функции гирлянды:
По гирлянде движется светодиод(два светодиода) в одну или другую сторону.
У гирлянды есть 3 кнопки для изменения режима работы:  
 1)Изменение скорости движения светодиодов (4 скорости – заж. И пот. 1с, 0.5, 0.25, 0.04)  
 2)Изменение направления движения (по часовой стрелки и против)  
 3)Изменение режима (1 или 2 огня)  
Ограничения:
Нажатия нескольких кнопок будет игнорироваться  
Для плавного зажигания и затухания используется ШИМ сигнал
