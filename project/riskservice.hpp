/**
 * riskservice.hpp
 * Defines the data types and Service for fixed income risk.
 *
 * @author Breman Thuraisingham
 */
#ifndef RISK_SERVICE_HPP
#define RISK_SERVICE_HPP

#include "soa.hpp"
#include "positionservice.hpp"

/**
 * PV01 risk.
 * Type T is the product type.
 */
template<typename T>
class PV01
{

public:

  // ctor for a PV01 value
  PV01(const T &_product, double _pv01, long _quantity);

  // Get the product on this PV01 value
  const T& GetProduct() const;

  // Get the PV01 value
  double GetPV01() const;

  // Get the quantity that this risk value is associated with
  long GetQuantity() const;

private:
  T product;
  double pv01;
  long quantity;

};



template<typename T>
PV01<T>::PV01(const T &_product, double _pv01, long _quantity) :
  product(_product)
{
  pv01 = _pv01;
  quantity = _quantity;
}


template<typenname T>
PV01<T>::GetProduct()
{
  return product;
}

template<typename T>
PV01<T>::GetPV01()
{
  return pv01;
}

template<typename T>
PV01<T>::GetQuantity()
{
  return quantity;
}





/**
 * A bucket sector to bucket a group of securities.
 * We can then aggregate bucketed risk to this bucket.
 * Type T is the product type.
 */
template<typename T>
class BucketedSector
{

public:

  // ctor for a bucket sector
  BucketedSector(const vector<T> &_products, string _name);

  // Get the products associated with this bucket
  const vector<T>& GetProducts() const;

  // Get the name of the bucket
  const string& GetName() const;

private:
  vector<T> products;
  string name;

};


template<typename T>
BucketedSector<T>::BucketedSector(const vector<T>& _products, string _name) :
  products(_products)
{
  name = _name;
}

template<typename T>
const vector<T>& BucketedSector<T>::GetProducts() const
{
  return products;
}

template<typename T>
const string& BucketedSector<T>::GetName() const
{
  return name;

};

/**
 * Risk Service to vend out risk for a particular security and across a risk bucketed sector.
 * Keyed on product identifier.
 * Type T is the product type.
 */
template<typename T>
class RiskService : public Service<string,PV01 <T> >
{

public:

  // Add a position that the service will risk
  void AddPosition(Position<T> &position) = 0;

  // Get the bucketed risk for the bucket sector
  const PV01<T>& GetBucketedRisk(const BucketedSector<T> &sector) const = 0;

};





class BondRiskService: public RiskService<Bond>
{

private:
  std::map<string,PV01<Bond> > RiskMP;
  std::vector< ServiceListener< PV01<Bond> >* > PositionListeners;

public:

  // Get data on our service given a key
  virtual PV01<Bond>& GetData(string key)
  {
    return RiskMP[key];
  }

  // The callback that a Connector should invoke for any new or updated data
  virtual void OnMessage(PV01<Bond> &data)
  {

  }

  // Add a listener to the Service for callbacks on add, remove, and update events
  // for data to the Service.
  virtual void AddListener(ServiceListener< PV01<Bond> > *listener)
  {
    PositionListeners.push_back(listener);
  }

  // Get all listeners on the Service.
  virtual const vector< ServiceListener< PV01<Bond> >* >& GetListeners() const
  {
    return PositionListeners;
  }


  // Add a position that the service will risk
  void AddPosition(Position< Bond > &position)
  {
    string productID = position.GetProduct().GetProductId();

    long posBook1 = position.GetPosition("TRSY1");
    long posBook2 = position.GetPosition("TRSY2");
    long posBook3 = position.GetPosition("TRSY3");
    long aggPos = position.GetAggregatePosition();



    if(PositionMP.find(productID)== PositionMP.end())
    {  
      if(productID == "2Y")
      {
        
          BondIdType idType = CUSIP;
          date maturityDate(2019,Oct,31);
          const Bond bond2Y("2Y", idType, "T", 0.015, maturityDate);
          
          PV01<Bond> obj1 = PV01<Bond>(bond2Y,0.0021,aggPos);
          RiskMP.insert(std::pair<string,PV01<Bond> >(productID, obj1));
      }
      else if(productID == "3Y")
      {
          BondIdType idType = CUSIP;
          date maturityDate(2020,Nov,15);
          const Bond bond3Y("3Y", idType, "T", 0.0175, maturityDate);
          
          PV01<Bond> obj1 = PV01<Bond>(bond3Y,0.0021,aggPos);
          RiskMP.insert(std::pair<string,PV01<Bond> >(productID, obj1));

      }
      else if(productID == "5Y")
      {
          BondIdType idType = CUSIP;
          date maturityDate(2022,Oct,31);
          const Bond bond5Y("5Y", idType, "T", 0.02, maturityDate);

          PV01<Bond> obj1 = PV01<Bond>(bond5Y,0.0021,aggPos);
          RiskMP.insert(std::pair<string,PV01<Bond> >(productID, obj1));
      }
      else if(productID == "7Y")
      {
          BondIdType idType = CUSIP;
          date maturityDate(2024,Oct,31);
          const Bond bond7Y("7Y", idType, "T", 0.0225, maturityDate);
          
          PV01<Bond> obj1 = PV01<Bond>(bond7Y,0.0021,aggPos);
          RiskMP.insert(std::pair<string,PV01<Bond> >(productID, obj1));

      }
      else if(productID == "10Y")
      {
          BondIdType idType = CUSIP;
          date maturityDate(2027,Nov,15);
          const Bond bond10Y("10Y", idType, "T", 0.0225, maturityDate);

          
          PV01<Bond> obj1 = PV01<Bond>(bond10Y,0.0021,aggPos);
          RiskMP.insert(std::pair<string,PV01<Bond> >(productID, obj1));
      }
      else if(productID == "30Y")
      {
          BondIdType idType = CUSIP;
          date maturityDate(2047,Nov,15);
          const Bond bond30Y("30Y", idType, "T", 0.0275, maturityDate); 
          
          PV01<Bond> obj1 = PV01<Bond>(bond30Y,0.0021,aggPos);
          RiskMP.insert(std::pair<string,PV01<Bond> >(productID, obj1));
      }
    }
    else
    {
      if(productID == "2Y")
      {
        
          BondIdType idType = CUSIP;
          date maturityDate(2019,Oct,31);
          const Bond bond2Y("2Y", idType, "T", 0.015, maturityDate);
          
          PV01<Bond> obj1 = PV01<Bond>(bond2Y,0.0021,aggPos);
          RiskMP[productID] = obj1;

      }
      else if(productID == "3Y")
      {
          BondIdType idType = CUSIP;
          date maturityDate(2020,Nov,15);
          const Bond bond3Y("3Y", idType, "T", 0.0175, maturityDate);
          
          PV01<Bond> obj1 = PV01<Bond>(bond3Y,0.0021,aggPos);
          RiskMP[productID] = obj1;
      }
      else if(productID == "5Y")
      {
          BondIdType idType = CUSIP;
          date maturityDate(2022,Oct,31);
          const Bond bond5Y("5Y", idType, "T", 0.02, maturityDate);

         PV01<Bond> obj1 = PV01<Bond>(bond5Y,0.0021,aggPos);
         RiskMP[productID] = obj1;
  
      }
      else if(productID == "7Y")
      {
          BondIdType idType = CUSIP;
          date maturityDate(2024,Oct,31);
          const Bond bond7Y("7Y", idType, "T", 0.0225, maturityDate);
          
          PV01<Bond> obj1 = PV01<Bond>(bond7Y,0.0021,aggPos);
          RiskMP[productID] = obj1;
      }
      else if(productID == "10Y")
      {
          BondIdType idType = CUSIP;
          date maturityDate(2027,Nov,15);
          const Bond bond10Y("10Y", idType, "T", 0.0225, maturityDate);
       
          PV01<Bond> obj1 = PV01<Bond>(bond10Y,0.0021,aggPos);
          RiskMP[productID] = obj1;
   
      }
      else if(productID == "30Y")
      {
          BondIdType idType = CUSIP;
          date maturityDate(2047,Nov,15);
          const Bond bond30Y("30Y", idType, "T", 0.0275, maturityDate); 
          
          PV01<Bond> obj1 = PV01<Bond>(bond30Y,0.0021,aggPos);
          RiskMP[productID] = obj1;
      }
    }

  }

  
  // Get the bucketed risk for the bucket sector
  const PV01<Bond>& GetBucketedRisk(const BucketedSector<Bond> &sector) const
  {
      string bucket = sector.GetName();
      vector<Bond> basket = sector.GetProducts();

      double pv01 = 0;
      double pos = 0;
      for(int i = 0; i<sector.size();i++)
      {
        pv01 += RiskMP[sector[i].GetProductId()].GetPV01()*RiskMP[sector[i].GetProductId()].GetQuantity();
        pos += RiskMP[sector[i].GetProductId()].GetQuantity();
      }

      pv01 = pv01/pos;


      if(bucket == "2Y")
      {
        
          BondIdType idType = CUSIP;
          date maturityDate(2019,Oct,31);
          const Bond bond2Y("2Y", idType, "T", 0.015, maturityDate);
          
          PV01<Bond> obj1 = PV01<Bond>(bond2Y,pv01,pos);
          return obj1;

      }
      else if(bucket == "3Y")
      {
          BondIdType idType = CUSIP;
          date maturityDate(2020,Nov,15);
          const Bond bond3Y("3Y", idType, "T", 0.0175, maturityDate);
          
          PV01<Bond> obj1 = PV01<Bond>(bond3Y,pv01,pos);
          return obj1;
      }
      else if(bucket == "5Y")
      {
          BondIdType idType = CUSIP;
          date maturityDate(2022,Oct,31);
          const Bond bond5Y("5Y", idType, "T", 0.02, maturityDate);

         PV01<Bond> obj1 = PV01<Bond>(bond5Y,pv01,pos);
          return obj1;
  
      }
      else if(bucket == "7Y")
      {
          BondIdType idType = CUSIP;
          date maturityDate(2024,Oct,31);
          const Bond bond7Y("7Y", idType, "T", 0.0225, maturityDate);
          
          PV01<Bond> obj1 = PV01<Bond>(bond7Y,pv01,pos);
          return obj1;
      }
      else if(bucket == "10Y")
      {
          BondIdType idType = CUSIP;
          date maturityDate(2027,Nov,15);
          const Bond bond10Y("10Y", idType, "T", 0.0225, maturityDate);
       
         PV01<Bond> obj1 = PV01<Bond>(bond10Y,pv01,pos);
          return obj1;
   
      }
      else if(bucket == "30Y")
      {
          BondIdType idType = CUSIP;
          date maturityDate(2047,Nov,15);
          const Bond bond30Y("30Y", idType, "T", 0.0275, maturityDate); 
          
         PV01<Bond> obj1 = PV01<Bond>(bond30Y,pv01,pos);
          return obj1;
      }

  }

}


class BondPositionRiskServiceListener : public ServiceListener< Position<Bond> >
{
  public:
   
    BondPositionRiskService(BondRiskService* bondRiskService_):riskService(bondRiskService_){};
    
    // Listener callback to process an add event to the Service
  virtual void ProcessAdd(Position<Bond> &data)
  {
    //std::cout<<"Listern 1"<<std::endl;
    riskService->AddPosition(data);
    //std::cout<<"Listern 2"<<std::endl;
  }

  // Listener callback to process a remove event to the Service
  virtual void ProcessRemove(Position<Bond> &data)
  {

  }

  // Listener callback to process an update event to the Service
  virtual void ProcessUpdate(Position<Bond> &data)
  {

  }

  private:

  BondRiskService* riskService;

};





#endif
