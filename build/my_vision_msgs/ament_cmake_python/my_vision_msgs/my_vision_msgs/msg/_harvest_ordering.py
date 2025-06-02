# generated from rosidl_generator_py/resource/_idl.py.em
# with input from my_vision_msgs:msg/HarvestOrdering.idl
# generated code does not contain a copyright notice


# Import statements for member types

# Member 'crop_ids'
import array  # noqa: E402, I100

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_HarvestOrdering(type):
    """Metaclass of message 'HarvestOrdering'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('my_vision_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'my_vision_msgs.msg.HarvestOrdering')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__harvest_ordering
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__harvest_ordering
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__harvest_ordering
            cls._TYPE_SUPPORT = module.type_support_msg__msg__harvest_ordering
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__harvest_ordering

            from my_vision_msgs.msg import DetectedCrop
            if DetectedCrop.__class__._TYPE_SUPPORT is None:
                DetectedCrop.__class__.__import_type_support__()

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class HarvestOrdering(metaclass=Metaclass_HarvestOrdering):
    """Message class 'HarvestOrdering'."""

    __slots__ = [
        '_header',
        '_crop_ids',
        '_objects',
        '_total_objects',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'crop_ids': 'sequence<uint32>',
        'objects': 'sequence<my_vision_msgs/DetectedCrop>',
        'total_objects': 'uint32',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('uint32')),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['my_vision_msgs', 'msg'], 'DetectedCrop')),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.crop_ids = array.array('I', kwargs.get('crop_ids', []))
        self.objects = kwargs.get('objects', [])
        self.total_objects = kwargs.get('total_objects', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.header != other.header:
            return False
        if self.crop_ids != other.crop_ids:
            return False
        if self.objects != other.objects:
            return False
        if self.total_objects != other.total_objects:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def header(self):
        """Message field 'header'."""
        return self._header

    @header.setter
    def header(self, value):
        if __debug__:
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'header' field must be a sub message of type 'Header'"
        self._header = value

    @builtins.property
    def crop_ids(self):
        """Message field 'crop_ids'."""
        return self._crop_ids

    @crop_ids.setter
    def crop_ids(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'I', \
                "The 'crop_ids' array.array() must have the type code of 'I'"
            self._crop_ids = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, int) for v in value) and
                 all(val >= 0 and val < 4294967296 for val in value)), \
                "The 'crop_ids' field must be a set or sequence and each value of type 'int' and each unsigned integer in [0, 4294967295]"
        self._crop_ids = array.array('I', value)

    @builtins.property
    def objects(self):
        """Message field 'objects'."""
        return self._objects

    @objects.setter
    def objects(self, value):
        if __debug__:
            from my_vision_msgs.msg import DetectedCrop
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, DetectedCrop) for v in value) and
                 True), \
                "The 'objects' field must be a set or sequence and each value of type 'DetectedCrop'"
        self._objects = value

    @builtins.property
    def total_objects(self):
        """Message field 'total_objects'."""
        return self._total_objects

    @total_objects.setter
    def total_objects(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'total_objects' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'total_objects' field must be an unsigned integer in [0, 4294967295]"
        self._total_objects = value
