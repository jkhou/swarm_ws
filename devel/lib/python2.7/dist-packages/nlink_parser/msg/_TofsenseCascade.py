# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from nlink_parser/TofsenseCascade.msg. Do not edit."""
import codecs
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import nlink_parser.msg

class TofsenseCascade(genpy.Message):
  _md5sum = "6f5a4318b44b44ec8258733a82bf1f6c"
  _type = "nlink_parser/TofsenseCascade"
  _has_header = False  # flag to mark the presence of a Header object
  _full_text = """TofsenseFrame0[] nodes

================================================================================
MSG: nlink_parser/TofsenseFrame0
uint8 id
uint32 system_time
float32 dis
uint8 dis_status
uint16 signal_strength
"""
  __slots__ = ['nodes']
  _slot_types = ['nlink_parser/TofsenseFrame0[]']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       nodes

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(TofsenseCascade, self).__init__(*args, **kwds)
      # message fields cannot be None, assign default values for those that are
      if self.nodes is None:
        self.nodes = []
    else:
      self.nodes = []

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
      length = len(self.nodes)
      buff.write(_struct_I.pack(length))
      for val1 in self.nodes:
        _x = val1
        buff.write(_get_struct_BIfBH().pack(_x.id, _x.system_time, _x.dis, _x.dis_status, _x.signal_strength))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      if self.nodes is None:
        self.nodes = None
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.nodes = []
      for i in range(0, length):
        val1 = nlink_parser.msg.TofsenseFrame0()
        _x = val1
        start = end
        end += 12
        (_x.id, _x.system_time, _x.dis, _x.dis_status, _x.signal_strength,) = _get_struct_BIfBH().unpack(str[start:end])
        self.nodes.append(val1)
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
      length = len(self.nodes)
      buff.write(_struct_I.pack(length))
      for val1 in self.nodes:
        _x = val1
        buff.write(_get_struct_BIfBH().pack(_x.id, _x.system_time, _x.dis, _x.dis_status, _x.signal_strength))
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
      if self.nodes is None:
        self.nodes = None
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.nodes = []
      for i in range(0, length):
        val1 = nlink_parser.msg.TofsenseFrame0()
        _x = val1
        start = end
        end += 12
        (_x.id, _x.system_time, _x.dis, _x.dis_status, _x.signal_strength,) = _get_struct_BIfBH().unpack(str[start:end])
        self.nodes.append(val1)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_BIfBH = None
def _get_struct_BIfBH():
    global _struct_BIfBH
    if _struct_BIfBH is None:
        _struct_BIfBH = struct.Struct("<BIfBH")
    return _struct_BIfBH
