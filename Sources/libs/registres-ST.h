// définitions pour les registres des deux composants ST liés en esclave au bus SPI du ColdFire
// Niels Grataloup & Brice Jacquin 28/03/2012


// définitions pour les registres dont les adresses sont communes pour les deux composants

#define ST_WHO_AM_I		0x0F
#define ST_CTRL_REG1	0x20
#define ST_CTRL_REG2	0x21
#define ST_CTRL_REG3	0x22
#define ST_CTRL_REG4	0x23
#define ST_CTRL_REG5	0x24

#define ST_STATUS_REG	0x27

#define ST_OUT_X_L		0x28
#define ST_OUT_X_H		0x29
#define ST_OUT_Y_L		0x2A
#define ST_OUT_Y_H		0x2B
#define ST_OUT_Z_L		0x2C
#define ST_OUT_Z_H		0x2D

#define ST_INT1_CFG		0x30
#define ST_INT1_SOURCE	0x31



// définitions propres à l'accéléromètre:

#define ST_ACC_HP_FILTER_RESET	0x25
#define ST_ACC_REFERENCE 		0x26

#define ST_ACC_INT1_THS			0x32
#define ST_ACC_INT1_DURATION 	0x33
#define ST_ACC_INT2_CFG 		0x34
#define ST_ACC_INT2_SOURCE 		0x35
#define ST_ACC_INT2_THS 		0x36
#define ST_ACC_INT2_DURATION 	0x37



// définitions propres au gyroscope

#define ST_GYRO_REFERENCE 		0x25
#define ST_GYRO_OUT_TEMP 		0x26

#define ST_GYRO_FIFO_CTRL_REG 	0x2E
#define ST_GYRO_FIFO_SRC_REG 	0x2F
#define ST_GYRO_INT1_TSH_XH 	0x32
#define ST_GYRO_INT1_TSH_XL 	0x33
#define ST_GYRO_INT1_TSH_YH 	0x34
#define ST_GYRO_INT1_TSH_YL 	0x35
#define ST_GYRO_INT1_TSH_ZH 	0x36
#define ST_GYRO_INT1_TSH_ZL 	0x37
#define ST_GYRO_INT1_DURATION 	0x38