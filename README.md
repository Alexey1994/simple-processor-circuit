# Простая схема процессора
Этот процессор может быть выполнен на транзисторах в домашних условиях. Битность можно задать любую. Здесь представлена схема 4-х битного варианта.
#
Для просмотра схемы используйте Logic Circuit: https://www.logiccircuit.org/
#
Формат комманды следующий:
1) 0-й бит: комманда, если 0, то комманда записи из регистра-аккумулятора в адрес, заданный в битах 2...N, если 1 то чтение из адреса в регистр-аккумулятор
2) 1-й бит: условное выполнения, если значение 1 то текущая комманда выполняется в любом случае, если 0 то выполнится только если в регистре-аккумуляторе не все нули
3) 2-N биты: адрес в little-endian 
#
Из-за особенностей представления кода 2 первых бита не используются в кодировании адреса, потому память для 4-х битного процессора адресуется 2-мя битами, т.е. всего 4 ячейки доступны, из них ячейка 00 отведена под 2-х битный program counter, 01 - RAM, 02, 03 - ПЗУ. Для адресации некоторого количества памяти нужно на 2 бита больше, например для адресации 64 КБ памяти нужна разрядность процессора в 18 бит.