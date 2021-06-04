# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from nlink_parser/LinktrackTag.msg. Do not edit."""
import codecs
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class LinktrackTag(genpy.Message):
  _md5sum = "4a4bf3020fbef59e2422a9233d276302"
  _type = "nlink_parser/LinktrackTag"
  _has_header = False  # flag to mark the presence of a Header object
  _full_text = """uint8 role
uint8 id
float32[3] pos_3d
float32[8] dis_arr
"""
  __slots__ = ['role','id','pos_3d','dis_arr']
  _slot_types = ['uint8','uint8','float32[3]','float32[8]']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       role,id,pos_3d,dis_arr

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(LinktrackTag, self).__init__(*args, **kwds)
      # message fields cannot be None, assign default values for those that are
      if self.role is None:
        self.role = 0
      if self.id is None:
        self.id = 0
      if self.pos_3d is None:
        self.pos_3d = [0.] * 3
      if self.dis_arr is None:
        self.dis_arr = [0.] * 8
    else:
      self.role = 0
      self.id = 0
      self.pos_3d = [0.] * 3
      self.dis_arr = [0.] * 8

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_get_struct_2B().pack(_x.role, _x.id))
      buff.write(_get_struct_3f().pack(*self.pos_3d))
      buff.write(_get_struct_8f().pack(*self.dis_arr))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      end = 0
      _x = self
      start = end
      end += 2
      (_x.role, _x.id,) = _get_struct_2B().unpack(str[start:end])
      start = end
      end += 12
      self.pos_3d = _get_struct_3f().unpack(str[start:end])
      start = end
      end += 32
      self.dis_arr = _get_struct_8f().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_get_struct_2B().pack(_x.role, _x.id))
      buff.write(self.pos_3d.tostring())
      buff.write(self.dis_arr.tostring())
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      end = 0
      _x = self
      start = end
      end += 2
      (_x.role, _x.id,) = _get_struct_2B().unpack(str[start:end])
      start = end
      end += 12
      self.pos_3d = numpy.frombuffer(str[start:end], dtype=numpy.float32, count=3)
      start = end
      end += 32
      self.dis_arr = numpy.frombuffer(str[start:end], dtype=numpy.float32, count=8)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_2B = None
def _get_struct_2B():
    global _struct_2B
    if _struct_2B is None:
        _struct_2B = struct.Struct("<2B")
    return _struct_2B
_struct_3f = None
def _get_struct_3f():
    global _struct_3f
    if _struct_3f is None:
        _struct_3f = struct.Struct("<3f")
    return _struct_3f
_struct_8f = None
def _get_struct_8f():
    global _struct_8f
    if _struct_8f is None:
        _struct_8f = struct.Struct("<8f")
    return _struct_8f