#include "TickerDataResult.h"

String price;
String volume;
String change;
String lastUpdatedAt;

TickerDataResult::TickerDataResult(String _price, String _volume, String _change, String _lastUpdatedAt) {
  price = _price;
  volume = _volume;
  change = _change;
  lastUpdatedAt = _lastUpdatedAt;
}

String TickerDataResult::getPrice() {
  return price;
}

String TickerDataResult::getVolume() {
  return volume;
}

String TickerDataResult::getChange() {
  return change;
}

String TickerDataResult::getLastUpdatedAt() {
  return lastUpdatedAt;
}