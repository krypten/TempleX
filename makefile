CC = g++
CFLAGS = -Wall -std=c++11
LDFLAGS = -lm

all : templeX

Model.o : Parser/Model/Model.cpp Parser/Model/Model.h
	${CC} ${CFLAGS} -c Parser/Model/Model.cpp

Parser.o : Parser/Parser.cpp Parser/Parser.h
	${CC} ${CFLAGS} -c Parser/Parser.cpp

XmlDOMData.o : Parser/XML/XmlDOMData.cpp Parser/XML/XmlDOMData.h
	${CC} ${CFLAGS} -c Parser/XML/XmlDOMData.cpp

XmlDOMAttribute.o : Parser/XML/XmlDOMAttribute.cpp Parser/XML/XmlDOMAttribute.h
	${CC} ${CFLAGS} -c Parser/XML/XmlDOMAttribute.cpp

XmlDOMNode.o : Parser/XML/XmlDOMNode.cpp Parser/XML/XmlDOMNode.h Parser/XML/XmlDOMData.h Parser/XML/XmlDOMAttribute.h
	${CC} ${CFLAGS} -c Parser/XML/XmlDOMNode.cpp

XmlDOMParser.o : Parser/XML/XmlDOMParser.cpp Parser/XML/XmlDOMNode.h Parser.o
	${CC} ${CFLAGS} -c Parser/XML/XmlDOMParser.cpp

JsonDOMValue.o : Parser/JSON/JsonDOMValue.cpp Parser/JSON/JsonDOMValue.h
	${CC} ${CFLAGS} -c Parser/JSON/JsonDOMValue.cpp

JsonDOMObject.o : Parser/JSON/JsonDOMObject.cpp Parser/JSON/JsonDOMObject.h Parser/JSON/JsonDOMValue.h
	${CC} ${CFLAGS} -c Parser/JSON/JsonDOMObject.cpp

JsonDOMParser.o : Parser/JSON/JsonDOMParser.cpp Parser/JSON/JsonDOMObject.h Parser.o
	${CC} ${CFLAGS} -c Parser/JSON/JsonDOMParser.cpp Parser/JSON/JsonDOMObject.h

ConvertUtil.o : Parser/ConvertUtil.cpp Parser/ConvertUtil.h Parser.o
	${CC} ${CFLAGS} -c Parser/ConvertUtil.cpp Parser/ConvertUtil.h

templex.o : templex.cpp Parser/ConvertUtil.h Parser/XML/XmlDOMNode.h Parser/JSON/JsonDOMObject.h
	${CC} ${CFLAGS} -c templex.cpp

templeX : templex.o Model.o ConvertUtil.o XmlDOMParser.o XmlDOMNode.o XmlDOMData.o XmlDOMAttribute.o JsonDOMParser.o JsonDOMObject.o JsonDOMValue.o
	${CC} ${CFLAGS} templex.o Model.o Parser.o ConvertUtil.o XmlDOMParser.o XmlDOMNode.o XmlDOMData.o XmlDOMAttribute.o JsonDOMParser.o JsonDOMObject.o JsonDOMValue.o ${LDFLAGS} -o TempleX
