#include "iodefine.h"
#include "machine.h"
#include <stdint.h>
#define USE_CMT			(0)
#define DELAY_50ns()	nop()
#define DELAY_250ns()	nop();nop();nop()
#define DELAY_500ns()	DELAY_250ns();DELAY_250ns()
#define DELAY_1us()		DELAY_500ns();DELAY_500ns()

void LCD_HALInit( void ){
#if USE_CMT
    /***** CMT2�`���l���̏����� *****/
    MSTP(CMT2) = 0;                        /* CMT���j�b�g1(CMT2�`���l��)���W���[���X�g�b�v������ */
    CMT2.CMCOR = 60 - 1;                           /* CMT2.CMCOR�ɃR���y�A�}�b�`������ݒ�(1�ʕb) */
    CMT2.CMCR.WORD = 0x00C0;             /* ���ӃN���b�NPCLK=48MHz��8������ݒ� CMT2���荞�݋��� */
#endif
    /***** LCD�p�|�[�g�̏����� *****/
    PORT5.DR.BYTE  &= 0xf8;                              /* �����f�[�^E="L",R/W="L",RS="L"��ݒ� */
    PORT5.DDR.BYTE |= 0x07;                       /* E,R/W,RS�[�q�ɐڑ����ꂽP52-P50���o�͂ɐݒ� */
    PORT9.DDR.BYTE |= 0x0f;                        /* DB7-DB4�[�q�ɐڑ����ꂽP93-P90���o�͂ɐݒ� */
}

/*""FUNC COMMENT""*********************************************************************************
 * ID         : ---
 * �֐���     : LCD_HALWait
 * �@�\       : 1��s�P�ʂ̃E�F�C�g
 * ����       : int time : �҂�����(1��s�~time)
 * �ԋp�l     : �Ȃ�
 * �g�p�֐�   : �Ȃ�
 * ���ӎ���   : �Ȃ�
 * History    : 
 *""FUNC COMMENT END""****************************************************************************/
void LCD_HALWait(uint32_t time)
{
#if USE_CMT
    CMT.CMSTR1.BIT.STR2 = 1;
    while(time--){
        while(!IR(CMT2, CMI2));
        IR(CMT2, CMI2) = 0;
    }
    CMT.CMSTR1.BIT.STR2 = 0;
    CMT2.CMCNT = 0;
#else
    while( time-- ){
    	DELAY_1us();
    }
#endif
}

/*""FUNC COMMENT""*********************************************************************************
 * ID         : ---
 * �֐���     : LCD_HALWriteNibbleCreg
 * �@�\       : �R�}���h���W�X�^�ւ̏�������(4�r�b�g)
 * ����       : uint8_t data : �������ޒl(����4�r�b�g�̂ݗL��)
 * �ԋp�l     : �Ȃ�
 * �g�p�֐�   : �Ȃ�
 * ���ӎ���   : 1.LCD������������݌Œ�(CPU:�o��,LCD:����)�ōs�����߂̏����ݒ�ς݂ł��B
 *            :   �EE,R/W,RS�[�q�ɐڑ����ꂽP52-P50�̏o�͕����ݒ�
 *            :   �EDB7-DB4�[�q�ɐڑ����ꂽP93-P90�̏o�͕����ݒ�
 *            :   �ER/W�[�q��"L"�ݒ�(��������)
 *            : 2.LCD����̂��߂̃^�C�~���O���m�ۂ���K�v������܂��B
 *            :   �ERS�Z�b�g�A�b�v�^�C��:40ns�ȏ�(E�[�q�������オ��O��RS�[�q"L"�̊���)
 *            :   �E�C�l�[�u���p���X��:220ns�ȏ�(E�[�q��"H"�̊���)
 *            :   �E�C�l�[�u���T�C�N���^�C��:500ns�ȏ�(E�[�q�������オ�����)
 *            : 3.ICLK=96MHz�̂���nop�֐��Ăяo���̃\�t�g�E�F�A�E�F�C�g�͖�10.4ns�ł��B
 * History    : 
 *""FUNC COMMENT END""****************************************************************************/
void LCD_HALWriteNibbleCreg(uint8_t data)
{
    PORT9.DR.BYTE = data;              /* �������ޒl���o�� */
    PORT5.DR.BIT.B0 = 0;               /* �R�}���h��I��(RS�[�q="L") */
    DELAY_50ns();
    PORT5.DR.BIT.B2 = 1;               /* E�[�q="H" */
    DELAY_250ns();
    PORT5.DR.BIT.B2 = 0;               /* E�[�q="L" */
    DELAY_250ns();
}

/*""FUNC COMMENT""*********************************************************************************
 * ID         : ---
 * �֐���     : LCD_HALWriteNibbleDreg
 * �@�\       : �f�[�^���W�X�^�ւ̏�������(4�r�b�g)
 * ����       : uint8_t data : �������ޒl(����4�r�b�g�̂ݗL��)
 * �ԋp�l     : �Ȃ�
 * �g�p�֐�   : �Ȃ�
 * ���ӎ���   : 1.LCD������������݌Œ�(CPU:�o��,LCD:����)�ōs�����߂̏����ݒ�ς݂ł��B
 *            :   �EE,R/W,RS�[�q�ɐڑ����ꂽP52-P50�̏o�͕����ݒ�
 *            :   �EDB7-DB4�[�q�ɐڑ����ꂽP93-P90�̏o�͕����ݒ�
 *            :   �ER/W�[�q��"L"�ݒ�(��������)
 *            : 2.LCD����̂��߂̃^�C�~���O���m�ۂ���K�v������܂��B
 *            :   �ERS�Z�b�g�A�b�v�^�C��:40ns�ȏ�(E�[�q�������オ��O��RS�[�q"L"�̊���)
 *            :   �E�C�l�[�u���p���X��:220ns�ȏ�(E�[�q��"H"�̊���)
 *            :   �E�C�l�[�u���T�C�N���^�C��:500ns�ȏ�(E�[�q�������オ�����)
 *            : 3.ICLK=96MHz�̂���nop�֐��Ăяo���̃\�t�g�E�F�A�E�F�C�g�͖�10.4ns�ł��B
 * History    : 
 *""FUNC COMMENT END""****************************************************************************/
void LCD_HALWriteNibbleDreg(uint8_t data)
{
    PORT9.DR.BYTE = data;              /* �������ޒl���o�� */
    PORT5.DR.BIT.B0 = 1;               /* �f�[�^��I��(RS�[�q="H") */
    DELAY_50ns();
    PORT5.DR.BIT.B2 = 1;               /* E�[�q="H" */
    DELAY_250ns();
    PORT5.DR.BIT.B2 = 0;               /* E�[�q="L" */
    DELAY_250ns();
}

void LCD_HALRefreshTimerInit(void){
    /***** CMT2�`���l���̏����� *****/
    MSTP(CMT2) = 0;                        /* CMT���j�b�g1(CMT2�`���l��)���W���[���X�g�b�v������ */
    CMT2.CMCOR = 60 - 1;                           /* CMT2.CMCOR�ɃR���y�A�}�b�`������ݒ�(1�ʕb) */
    CMT2.CMCR.WORD = 0x00C0;             /* ���ӃN���b�NPCLK=48MHz��8������ݒ� CMT2���荞�݋��� */
    IR( CMT2,CMI2) = 0;
    IEN( CMT2,CMI2 ) = 1;
}
