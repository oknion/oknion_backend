/*
 ============================================================================
 Name        : back-end-v3.cpp
 Author      : kienpc
 Version     :
 Copyright   : WPL
 Description : back-end thrift server
 ============================================================================
 */

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <fstream>
#include <unistd.h>
#include <memory>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <thrift/lib/cpp2/server/ThriftServer.h>
#include "storage/FollyCache.h"
#include "storage/LevelDbPersistence.h"
#include "ZListServiceSvImpl.h"

using namespace zingme::zlist::thrift::cpp2;
using namespace std;
using namespace vng_wpl::backend;

DEFINE_bool(daemon, false, "Create new process and exit this process");
DEFINE_string(dumpLocation, "dump",
    "Specify location for writing the failure dump");
DEFINE_int32(port, 0, "Port number thrift server will listen in ");

void dump_writer(const char* data, int size);

int main(int argc, char** argv) {
  using namespace apache::thrift;

  // set google log directory
  string runCmd(argv[0]);
  FLAGS_log_dir = runCmd.substr(0, runCmd.find_last_of("/"));

  // init logging, flags, stack dump
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  google::InstallFailureSignalHandler();
  google::InstallFailureWriter(dump_writer);
  gflags::SetUsageMessage("hoho");

  // start server on other process if daemon option enable
  if (FLAGS_daemon) {
    cout << "Create new process and exit this process" << endl;
    cout << "Thread id: " << getpid() << endl;
    pid_t process_id;
    process_id = fork();
    if (process_id != 0) {
      cout << "Main thread about to exit!" << endl;
      return 0;
    }
  }

  // start thrift server
  ThriftServer* s = new ThriftServer();
  LOG(INFO)<< "Starting server at port " << FLAGS_port;
  s->setPort(FLAGS_port);
  using namespace zingme::zlist::thrift::cpp2;
  auto ifptr = new ZListServiceSvImpl(
      new BasicStorage<ZKey, ZListItem>(StorageConfig(),
          new FollyCache<ZKey, ZListItem>(),
          new LevelDbPersistence<ZKey, ZListItem>()));
  std::shared_ptr<ZListServiceSvIf> itf(ifptr);
  s->setInterface(itf);
  s->serve();

  return 0;
}
void dump_writer(const char* data, int size) {
  std::ofstream myfile;
  myfile.open(FLAGS_dumpLocation, std::ios_base::app);
  string text(data, size);
  myfile << text << std::endl;
  myfile.close();
}
