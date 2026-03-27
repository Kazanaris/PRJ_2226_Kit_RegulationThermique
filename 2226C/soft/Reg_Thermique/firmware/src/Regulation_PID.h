/* ************************************************************************** */
/** Descriptive File Name

  @Company
    ETML-ES

  @File Name
    RegulationPID.h

  @Description
 *  Fichier h traitant la régulationPID
 */
/* ************************************************************************** */

#ifndef _REGULATION_PID_H    /* Guard against multiple inclusion */
#define _REGULATION_PID_H

#include "GestMenu.h"


void CalculPID(const S_ParamGainPID *ValGainPID, const S_ParamConsigne* ValConsigne, S_ValReglage* pReglage);


#endif /* _REGULATION_PID_H */

/* *****************************************************************************
 End of File
 */
