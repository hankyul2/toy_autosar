#ifndef vrtaLoggerDeviceH
#define vrtaLoggerDeviceH
/* --------------------------------------------------------------------------- */
/*  Defines the Logger device. */
/*   Can be used to send text output to zero, one or two files (including 'con') */
/*    e.g. Logger Screen("Screen", "con"); (/dev/stdout for VRTA-ux) */
/*   A specialization of a Logger that has the name "Status" can be used to show text on */
/*   the embedded GUI's status bar */
/*    e.g. Logger Status("Status"); */
/* --------------------------------------------------------------------------- */

#ifdef __linux__
 #include <stdio.h>
 #include <cstdarg>
#else
 #include <windows.h>
#endif

#include /* no inline */ "vrtaDevice.h"

/* --------------------------------------------------------------------------- */
class Logger : public vrtaDevice
/* --------------------------------------------------------------------------- */ {
#define MAX_LOGGER_BUFFER (10000)
#ifndef MAX_PATH
  #define MAX_PATH (4096)
#endif
private:
  Logger * m_AliasTo;
  bool m_Suspend;
  void * m_hOut;
  void * m_hDuplicate;
  char m_TextBuf[MAX_LOGGER_BUFFER];
  char m_EvTextBuf[MAX_LOGGER_BUFFER];

  struct s_persist {
    char outfile[MAX_PATH];
    char dupfile[MAX_PATH];
    vrtaUInt linecount;
  } m_Persist; /*  State that can be persisted over a reset */
  vrtaBoolean m_Started;

protected:
  void Starting(void);
  void Stopping(void);
  int  UpdateText(void);

  /*  Persistence */
  vrtaDataLen GetPersistentDataSize(void);
  vrtaByte * GetPersistentData(void);
  void SetPersistentData(vrtaByte *addr, vrtaDataLen len);

public:
  /*  Constructors */
  Logger(const vrtaTextPtr name);
  Logger(const vrtaTextPtr name, const vrtaTextPtr file);
  Logger(const vrtaTextPtr name, const vrtaTextPtr file1, const vrtaTextPtr file2);
  Logger(const vrtaTextPtr name, Logger &link); /*  Alias to another logger */

  /*  Device interface */
  vrtaErrType OnAction(const vrtaAction *action);
  vrtaErrType AsyncGetState(vrtaEvent *event);

  /*  Doers */
  int print(const vrtaTextPtr txt);
  int print(const vrtaTextPtr txt, vrtaUInt len);
  int printf(const vrtaTextPtr format, ...);
  int printf(const vrtaTextPtr format, va_list arglist);

  vrtaErrType setfile(const vrtaTextPtr txt); /*  Change the first file */
  vrtaErrType setduplicate(const vrtaTextPtr file);

  /*  Change the duplicate file */
  vrtaUInt linecount(void) {
    return m_Persist.linecount;
  };

  void suspend(bool f) {
    m_Suspend = f;
  };

};


/* --------------------------------------------------------------------------- */
#endif
