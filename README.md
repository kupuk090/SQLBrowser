Цель:   придумать как ускорить либо lessThan, либо саму сортировку
	убедиться в том, что proxy-модель всё замедлит
	копать в сторону: сортировка bigdata, ускорение QSortFilterProxyModel и подобное


sort - посмотреть (можно записать свой алгоритм)

в ПЗ - написать про сортировку силам самой модели (ORDER BY) и объяснить почему в этом мало смысла (как минимум при многопользовательской работе с бд)


найти способ для замера времени "сортировки" (к примеру следить за нажатием на заголовок и останавливаемся, когда заставили перерисовать QTableView)
попробовать прилепить ко всему этому потоки

придумать как засечь время для стандартной прокси-модели


https://code.woboq.org/qt5/qtbase/src/gui/itemmodels/qstandarditemmodel.cpp.html#_ZN20QStandardItemPrivate12sortChildrenEiN2Qt9SortOrderE глянуть реализацию
в стандартной модели попробвать засекать время в lessThan


QMap:
	Сортировка по столбцу "amount" в направлении 0 заняла:  2089 ms
	Сортировка по столбцу "fare_conditions" в направлении 0 заняла:  4786 ms
	Сортировка по столбцу "flight_id" в направлении 0 заняла:  2227 ms
	Сортировка по столбцу "ticket_no" в направлении 0 заняла:  7094 ms
Quick Sort:
	Сортировка по столбцу "amount" в направлении 0 заняла:  2314 ms
	Сортировка по столбцу "fare_conditions" в направлении 0 заняла:  3852 ms
	Сортировка по столбцу "flight_id" в направлении 0 заняла:  2551 ms
	Сортировка по столбцу "ticket_no" в направлении 0 заняла:  8138 ms
Heap Sort:
	Сортировка по столбцу "amount" в направлении 0 заняла:  2925 ms
	Сортировка по столбцу "fare_conditions" в направлении 0 заняла:  4975 ms
	Сортировка по столбцу "flight_id" в направлении 0 заняла:  3116 ms
	Сортировка по столбцу "ticket_no" в направлении 0 заняла:  8615 ms
Stable Sort:
	Сортировка по столбцу "amount" в направлении 0 заняла:  2353 ms
	Сортировка по столбцу "fare_conditions" в направлении 0 заняла:  2909 ms
	Сортировка по столбцу "flight_id" в направлении 0 заняла:  2490 ms
	Сортировка по столбцу "ticket_no" в направлении 0 заняла:  7357 ms
Simple Sort:
	Сортировка по столбцу "amount" в направлении 0 заняла:  2223 ms
	Сортировка по столбцу "fare_conditions" в направлении 0 заняла:  3582 ms
	Сортировка по столбцу "flight_id" в направлении 0 заняла:  2719 ms
	Сортировка по столбцу "ticket_no" в направлении 0 заняла:  8518 ms
