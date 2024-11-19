#include "DataReaderListenerImpl.h"
#include "Boilerplate.h"
#include <iostream>

using namespace examples::boilerplate;

DataReaderListenerImpl::DataReaderListenerImpl() : sample_count(0)
{
}

void
DataReaderListenerImpl::on_data_available(DDS::DataReader_ptr reader)
{
  // Safely downcast data reader to type-specific data reader
  Messenger::MessageDataReader_var reader_i = narrow(reader);

  Messenger::Message msg;
  DDS::SampleInfo info;

  // Remove (take) the next sample from the data reader
  DDS::ReturnCode_t error = reader_i->take_next_sample(msg, info);

  // Make sure take was successful
  if (error == DDS::RETCODE_OK) {
    // Make sure this is not a sample dispose message
    if (info.valid_data) {
      ++sample_count;
      std::cout << "Calculation Received: Value of A: " << msg.subject << std::endl
        << "                      Value of B: " << msg.count << std::endl
        << "                      Result of the operation: " << msg.subject_id << std::endl;
    }
  } else {
    ACE_ERROR((LM_ERROR,
               ACE_TEXT("ERROR: %N:%l: on_data_available() -")
               ACE_TEXT(" take_next_sample failed!\n")));
  }
}
