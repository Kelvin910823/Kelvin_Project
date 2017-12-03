
#include "soa.hpp"
#include "products.hpp"
//#include "positionservice.hpp"
#include "tradebookingservice.hpp"



int main()
{


	BondTradeBookingService bookingService;
	//BondPositionService positionService;

	//BondPositionServiceListener* posListener(&positionService);
	//bookingService.AddListener(posListener);

	BondTradeBookingServiceConnector BookingServiceCon(bookingService);
	BookingServiceCon.Subscribe();

	return 0;


}