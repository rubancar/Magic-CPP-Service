#include <ssqls.h>

sql_create_3(registro_luz, 1, 3,
            sql_datetime, fecha,
            sql_float, valor,
            sql_int, sensor);

sql_create_3(registro_temp, 1, 3,
            sql_datetime, fecha,
            sql_float, valor,
            sql_int, sensor);

sql_create_3(registro_humedad, 1, 3,
            sql_datetime, fecha,
            sql_float, valor,
            sql_int, sensor);
