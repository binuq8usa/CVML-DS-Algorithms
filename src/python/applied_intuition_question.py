"""Messages can be made up of floats, ints, strings.
Assume strings are 256 bytes, ints 4 bytes, and floats 4 bytes.

Example Input:

// Begin Input
Message Vehicle
float x_position
float y_position
float velocity
float acceleration
int num_wheels
string name

Message Vector2d
float x_position
float y_position
Message SomethingNew
...
// End Input

Please write a parser that parses the input value into a data structure that supports the following queries:

Given a message type name, output its size in bytes.
Given a message type name and message field, output the type as a string

Expected Outputs:

parser.get_size("Vehicle") -> 276
parser.get_size("Vector2d") -> 8
parser.get_size("float") -> 4
parser.get_type("Vehicle", "x_position") -> "float"
parser.get_type("Vehicle", "name") -> "string"
"""

"""
float  =4 
int = 4
string = 256

"""
from enum import Enum
from typing import Set, Tuple, List

MESSAGE="Message"
FLOAT="float"
INT="int"
STRING="string"
data_types = { 
    FLOAT: 4,
    INT: 4,
    STRING: 256
}

class Message:
    def __init__(self) -> None:
        self.message_type : str = ""
        # fields -> (field_name, field_type (in str))
        self.fields : List[Tuple[str, str]] = []  
    
    def get_size_of_basic_type(self, field_type : str):
        if field_type == INT or field_type == FLOAT:
            return 4
        elif field_type == STRING:
            return 256

    def get_size(self):
        total_size = 0
        for field in self.fields:
            total_size += self.get_size_of_basic_type(field)

                
class Parser:
    def __init__(self) -> None:
        self.list_of_messages : List[Message] = []

    def read_multiline_input(self, input_str : str):
        multi_lines = input_str.splitlines()

        # multi_lines will be a list of multi_lines
        curr_message : Message = Message()
        for line in multi_lines:
            if line == '\n':
                self.list_of_messages.append(curr_message)
                curr_message = Message()
                continue
            field_type, field_name = line.split(sep=" ")
            if field_type == MESSAGE:
                curr_message.message_type = MESSAGE
            else:
                curr_message.fields.append((field_name, data_types[field_type]))
    





