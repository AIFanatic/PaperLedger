#include "DataProvider.h"

DataSource *providers[2];

DataProvider::DataProvider(Manager *_manager) {
  manager = _manager;
  providers[0] = new CoinGecko(_manager);
  providers[1] = new BitcoinAverage(_manager);
}

DataSource *DataProvider::get() {
  int dataSource = manager->settings->get(DATA_SOURCE).toInt();

  for (DataSource *source : providers)
  {
    if (false == source->supports(dataSource)) {
      continue;
    }

    return source;
  }

  return NULL;
}