Цель:   придумать как ускорить либо lessThan, либо саму сортировку
	убедиться в том, что proxy-модель всё замедлит
	копать в сторону: сортировка bigdata, ускорение QSortFilterProxyModel и подобное


sort - посмотреть (можно записать свой алгоритм)

в ПЗ - написать про сортировку силам самой модели (ORDER BY) и объяснить почему в этом мало смысла (как минимум при многопользовательской работе с бд)



+заставить принудительно перерисоваться весь QTableView (что-то наподобие вызова reset/update)
найти способ для замера времени "сортировки" (к примеру следить за нажатием на заголовок и останавливаемся, когда заставили перерисовать QTableView)
потестить другие алгоритмы сортировки
попробовать прилепить ко всему этому потоки

придумать как засечь время для стандартной прокси-модели
