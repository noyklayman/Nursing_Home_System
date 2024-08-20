#ifndef _NURSING_HOME_HELPER
#define	_NURSING_HOME_HELPER

#include "NursingHome.h"


void		sortTenant(NursingHome* pNursing);
void		sortTenantById(NursingHome* pNursing);
void		sortGroupActivityName(NursingHome* pNursing);
eSortOption showSortMenu();
void		findTenant(const NursingHome* pNursing);
int			findTenantById(const NursingHome* pNursing);
int			findGroupActivityByName(const NursingHome* pNursing);




#endif
