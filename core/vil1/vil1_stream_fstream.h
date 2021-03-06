// This is core/vil1/vil1_stream_fstream.h
#ifndef vil1_stream_fstream_h_
#define vil1_stream_fstream_h_
#ifdef VCL_NEEDS_PRAGMA_INTERFACE
#pragma interface
#endif
//:
// \file
// \brief A vil1_stream implementation using std::fstream
// \author    awf@robots.ox.ac.uk
// \date 16 Feb 00

#include <fstream>
#include <vcl_compiler.h>
#include <vil1/vil1_stream.h>

//: A vil1_stream implementation using std::fstream
class vil1_stream_fstream : public vil1_stream
{
 public:
  vil1_stream_fstream(char const* filename, char const* mode);

  // implement virtual vil1_stream interface:
  bool ok() const { return f_.good(); }
  vil1_streampos write(void const* buf, vil1_streampos n);
  vil1_streampos read(void* buf, vil1_streampos n);
  vil1_streampos tell() const;
  void seek(vil1_streampos position);

 protected:
  ~vil1_stream_fstream();

 private:
  std::ios::openmode flags_;
  mutable std::fstream f_;
  int id_;
};

#endif // vil1_stream_fstream_h_
