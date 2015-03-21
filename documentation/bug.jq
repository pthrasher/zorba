serialize({ "api" : "zorba", "name" : "ft_thesaurus", "description" : [ "\n", "Introduction", "\n", "The Zorba XQuery engine implements the ", "XQuery and XPath Full Text 1.0", " specification that, among other things, adds the ability to use a thesaurus for text-matching via the ", "thesaurus option", ". For example, the query:", "let", "$x", ":=", "&lt;msg&gt;affluent", "man&lt;/msg&gt&quot;, "\n", "return", "$x", "contains", "text", "\"wealthy\"", "\n", "using", "thesaurus", "default", "\n", "returns ", "true", " because ", "$x", " contains \"wealthy\" that the thesaurus identified as a synonym of \"affluent\".", "The initial implementation of the thesaurus option uses the ", "WordNet lexical database", ", version 3.0.", "The stock WordNet database files are plain ASCII text files. In many ways this is very convenient for portability, grep-ability, vi-ability, etc. However, the sum total of the files is approximately 27MB (which is quite large) and accessing the database would be inefficient since the files would have to be parsed for every access.", "Instead, the database files are compiled into a single binary file that is 6MB and can be efficiently accessed from Zorba using ", "mmap(2)", " with no parsing of the data. The only caveat of the binary format is that it is endian-dependent, i.e., a binary file created on a computer having a little-endian CPU won't work on a computer having a big-endian CPU.", "\n", "Downloading &amp; Installing the WordNet Database", "\n", "To download and install the WordNet database on a Unix-like system, follow these steps:", "\n", "Download the WordNet database from ", "here", ". All you really need are just the database files (", "WNdb-3.0.tar.gz", ").", "Un-gzip and untar the files. This will result in a directory dict containing the database files.", "Move the dict directory somewhere of your choosing, e.g., ", "/usr/local/wordnet-3.0/dict", ".", "Compile the ", "dict", " directory into a Zorba-compatible binary thesaurus as
described below.", "\n", "To compile the WordNet database files, use the ", "zt-wn-compile", " script found in the ", "scripts", " subdirectory of the Zorba distribution. (Note: this script is written in perl.) The usage message is:", "zt-wn-compile", "[-v]", "wordnet_dict_dir", "[thesaurus_file]", "\n", "\n", "The ", "-v", " option specifies verbose output.", "The ", "wordnet_dict_dir", " specifies the full path of the WordNet ", "dict", " directory.", "The ", "thesaurus_file", " specifies the name of the resulting binary file. If none is given, it defaults to ", "wordnet-en.zth", " (\"en\" for English and \"zth\" for \"Zorba Thesaurus file\").", "\n", "For example:", "zt-wn-compile", "-v", "/usr/local/wordnet-3.0/dict", "\n", "To install the ", "wordnet-en.zth", " file, move it onto Zorba's ", "library path", ":", "LIB_PATH/edu/princeton/wordnet/wordnet-", "en", ".zth", "\n", "\n", "Downloading a Precompiled WordNet Database", "\n", "Alternatively, you can download a precompiled, little-endian (Intel) CPU WordNet database from ", "here", ".", "\n", "\n", "Thesauri Mappings", "\n", "In order to use thesauri, you need to specify what symbolic URI(s) ", "map", " to what thesauri. A mapping is of the form:", "from_uri", ":=", "implementation-scheme", ":", "to_uri", "For example:", "http:", "//wordnet.princeton.edu:=wordnet://wordnet.princeton.edu", "\n", "says that the symbolic URI ", "http://wordnet.princeton.edu", " maps to the WordNet implementation having a database file at the given sub-path ", "edu/princeton/wordnet", " on Zorba's library path. Once a mapping is established for a symbolic URI, it can be used in a query:", "let", "$x", ":=", "&lt;msg&gt;affluent", "man&lt;/msg&gt&quot;, "\n", "return", "$x", "contains", "text", "\"wealthy\"", "\n", "using", "thesaurus", "at", "\"http://wordnet.princeton.edu\"", "\n", "As a special-case, the ", "from_uri", " can be ", "default", " or ", "##default", " to allow for specifying the default thesaurus as was done for
the first example on this page.", "\n", "Specifying Thesauri Mappings to Zorba", "\n", "To specify the location of the thesaurus to Zorba from the command-line, use one or more –thesaurus options:", "zorba", "--thesaurus", "default", ":=wordnet:", "//wordnet.princeton.edu", "...", "\n", "\n", "Thesaurus Relationships", "\n", "Using the WordNet database, Zorba supports all of the thesaurus relationships specified by [ISO 2788] and [ANSI/NISO Z39.19-2005] with the exceptions of \"HN\" (history note) and \"X SN\" (see scope note for).", "\n", "ISO 2788 and ANSI/NISO Z39.19-2005 Relationships", "\n", "These relationships are:", " ", "\n", "Rel. ", "Meaning ", "WordNet Rel.  ", "\n", "\n", "BT ", "broader term ", "hypernym  ", "\n", "\n", "BTG ", "broader term generic ", "hypernym  ", "\n", "\n", "BTI ", "broader term instance ", "instance hypernym  ", "\n", "\n", "BTP ", "broader term partitive ", "part meronym  ", "\n", "\n", "\n", "\n", "\n", "\n", "\n", "\n", "\n", "\n", "NT ", "narrower term ", "hyponym  ", "\n", "NTG ", "narrower term generic ", "hyponym  ", "\n", "NTI ", "narrower term instance ", "instance hyponym  ", "\n", "NTP ", "narrower term partitive ", "part holonym  ", "\n", "RT ", "related term ", "also see  ", "\n", "SN ", "scope note ", "n/a  ", "\n", "TT ", "top term ", "hypernym  ", "\n", "UF ", "non-preferred term ", "n/a  ", "\n", "\n", "USE ", "preferred term ", "n/a  ", "\n", "and can be used in a query like:", "let", "$x", ":=", "&lt;msg&gt;breakfast", "of", "champions&lt;/msg&gt&quot;, "\n", "return", "$x", "contains", "text", "\"meal\"", "\n", "using", "thesaurus", "at", "\"http://wordnet.princeton.edu\"", "\n", "relationship", "\"NT\"", "\n", "that returns ", "true", " because ", "$x", " contains \"breakfast\" that the thesaurus identified as a \"narrower term\" (NT) of \"meal.\"", "Note that you can specify relationships either by their abbreviation or their meaning. Relationships are case-insensitive. The above query is equivalent to:",
"let", "$x", ":=", "&lt;msg&gt;breakfast", "of", "champions&lt;/msg&gt&quot;, "\n", "return", "$x", "contains", "text", "\"meal\"", "\n", "using", "thesaurus", "at", "\"http://wordnet.princeton.edu\"", "\n", "relationship", "\"narrower", "term\"", "\n", "Since Zorba's thesaurus is implemented using WordNet, the [ISO 2788] relationships map to WordNet relationships that are shown in the \"WordNet Rel.\" column. WordNet relationships are explained in the next section.", "\n", "\n", "WordNet Relationships", "\n", "In addition to the [ISO 2788] and [ANSI/NISO Z39.19-2005] relationships, Zorba also supports all of the relationships offered by WordNet. These relationships are:", " ", "\n", "Relationship ", "Meaning  ", "\n", "\n", "also", "see ", "A word that is related to another, e.g., for \"varnished\" (furniture) one should ", " \"finished.\"   ", "also see", "\n", "\n", "antonym ", "A word opposite in meaning to another, e.g., \"light\" is an ", " for \"heavy.\"   ", "antonym", "\n", "\n", "attribute ", "A noun for which adjectives express values, e.g., \"weight\" is an ", " for which the adjectives \"light\" and \"heavy\" express values.   ", "attribute", "\n", "\n", "cause ", "A verb that causes another, e.g., \"show\" is a ", " of \"see.\"   ", "cause", "\n", "\n", "\n", "\n", "\n", "\n", "\n", "\n", "\n", "\n", "\n", "\n", "\n", "\n", "\n", "\n", "\n", "\n", "\n", "derivationally", "related", "form ", "A word that is derived from a root word, e.g., \"metric\" is a ", "derivationally related form", " of \"meter.\"   ", "\n", "derived", "from", "adjective ", "An adverb that is derived from an adjective, e.g., \"correctly\" is ", "derived from the adjective", " \"correct.\"   ", "\n", "entailment ", "A verb that presupposes another, e.g., \"snoring\" ", "entails", " \"sleeping.\"   ", "\n", "hypernym ", "A word with a broad meaning that more specific words fall under, e.g., \"meal\" is a ", "hypernym", " of \"breakfast.\"   ", "\n", "hyponym ", "A word of more
specific meaning than a general term applicable to it, e.g., \"breakfast\" is a ", "hyponym", " of \"meal.\"   ", "\n", "instance", "hypernym ", "A word that denotes a category of some specific instance, e.g., \"author\" is an ", "instance hypernym", " of \"Asimov.\"   ", "\n", "instance", "hyponym ", "A term that donotes a specific instance of some general category, e.g., \"Asimov\" is an ", "instance hyponym", " of \"author.\"   ", "\n", "member", "holonym ", "A word that denotes a collection of individuals, e.g., \"faculty\" is a ", "member holonym", " of \"professor.\"   ", "\n", "member", "meronym ", "A word that denotes a member of a larger group, e.g., a \"person\" is a ", "member meronym", " of a \"crowd.\"   ", "\n", "part", "holonym ", "A word that denotes a larger whole comprised of some part, e.g., \"car\" is a ", "part holonym", " of \"engine.\"   ", "\n", "part", "meronym ", "A word that denotes a part of a larger whole, e.g., an \"engine\" is ", "part meronym", " of a \"car.\"   ", "\n", "participle", "of", "verb ", "An adjective that is the participle of some verb, e.g., \"breaking\" is the ", "participle of the verb", " \"break.\"   ", "\n", "pertainym ", "An adjective that classifies its noun, e.g., \"musical\" is a ", "pertainym", " in \"musical instrument.\"   ", "\n", "similar", "to ", "Similar, though not necessarily interchangeable, adjectives. For example, \"shiny\" is ", "similar to", " \"bright\", but they have subtle differences.   ", "\n", "substance", "holonym ", "A word that denotes a larger whole containing some constituent substance, e.g., \"bread\" is a ", "substance holonym", " of \"flour.\"   ", "\n", "substance", "meronym ", "A word that denotes a constituant substance of some larger whole, e.g., \"flour\" is a ", "substance meronym", " of \"bread.\"   ", "\n", "verb", "group ", "A verb that is a member of a group of similar verbs, e.g., \"live\" is in the ", "verb group", " of \"dwell\", \"live\", \"inhabit\", etc.   ", "\n",
"\n", "\n", "WordNet Levels", "\n", "If no levels are specified in a query, Zorba defaults the WordNet implementation to be 2 levels. (The rationale can be found ", "here", ".)", "\n", "\n", "Providing Your Own Thesaurus", "\n", "Using the Zorba C++ API, you can provide your own thesaurus by deriving from four classes: ", "Thesaurus", ", ", "Thesaurus::iterator", ", ", "ThesaurusProvider", ", and ", "URLResolver", ".", "\n", "The Thesaurus Class", "\n", "The ", "Thesaurus", " class is:", "class", "Thesaurus", "{", "\n", "public", ":", "\n", "typedef", "/*", "implementation-defined", "*/", "ptr&quot;, "\n", "typedef", "/*", "implementation-defined", "*/", "range_type&quot;, "\n", "\n", "class", "iterator", "{", "\n", "public", ":", "\n", "typedef", "/*", "implementation-defined", "*/", "ptr&quot;, "\n", "virtual", "void", "destroy()", "const", "=", "0&quot;, "\n", "virtual", "bool", "next(", "String", "*synonym", ")", "=", "0&quot;, "\n", "protected", ":", "\n", "virtual", "~iterator()&quot;, "\n", "}&quot;, "\n", "\n", "virtual", "iterator::ptr", "lookup(", "String", "const", "&amp;phrase,", "String", "const", "&amp;relationship,", "range_type", "at_least,", "range_type", "at_most", ")", "const", "=", "0&quot;, "\n", "\n", "virtual", "void", "destroy()", "const", "=", "0&quot;, "\n", "protected", ":", "\n", "virtual", "~Thesaurus()&quot;, "\n", "}&quot;, "\n", "For details about the ", "ptr", " types, the ", "destroy()", " functions, and why the destructors are ", "protected", ", see the ", "Memory Management", " document.", "To implement the ", "Thesaurus", " you need to implement the ", "lookup()", " function where:", "\n", "phrase", "  ", "The phrase to be looked-up.  ", "\n", "\n", "  ", "relationship", "The relationship the results are to have to the phrase, if any.  ", "\n", "\n", "  ", "at_least", "The minimum number of levels within the thesaurus to be traversed.  ", "\n", "\n", "  ", "at_most", "The maximum number of levels within the thesaurus to be
traversed.  ", "\n", "\n", "The ", "lookup()", " function returns a pointer to an ", "iterator", " that is used to iterate over the phrase's synonyms. You also need to implement an ", "iterator", ". A very simple ", "Thesaurus", " and its ", "iterator", " can be implemented as:", "class", "MyThesaurus", ":", "public", "Thesaurus", "{", "\n", "public", ":", "\n", "void", "destroy()", "const", "&quot;, "\n", "iterator::ptr", "lookup(", "String", "const", "&amp;phrase,", "String", "const", "&amp;relationship,", "range_type", "at_least,", "range_type", "at_most", ")", "const", "&quot;, "\n", "private", ":", "\n", "//", "\n", "//", "Define", "a", "simple", "thesaurus", "data", "structure", "as", "a", "map", "from", "a", "phrase", "to", "a", "list", "of", "its", "synonyms.", "\n", "//", "\n", "typedef", "std::list&lt;String&gt&quot;, "synonyms_type&quot;, "\n", "typedef", "std::map&lt;String,synonyms_type", "const*&gt&quot;, "thesaurus_data_type&quot;, "\n", "\n", "static", "thesaurus_data_type", "const", "&amp&quot;, "get_thesaurus_data()&quot;, "\n", "\n", "class", "iterator", ":", "public", "Thesaurus::iterator", "{", "\n", "public", ":", "\n", "iterator(", "synonyms_type", "const", "&amp;s", ")", ":", "synonyms_(", "s", "),", "i_(", "s.begin()", ")", "{", "}", "\n", "void", "destroy()&quot;, "\n", "bool", "next(", "String", "*synonym", ")&quot;, "\n", "private", ":", "\n", "synonyms_type", "const", "&amp;synonyms_&quot;, "//", "synonyms", "to", "iterate", "over", "\n", "synonyms_type::const_iterator", "i_&quot;, "//", "current", "iterator", "position", "\n", "}&quot;, "\n", "}&quot;, "\n", "\n", "void", "MyThesaurus::destroy()", "const", "{", "\n", "//", "Do", "nothing", "since", "we", "statically", "allocate", "a", "singleton", "instance", "of", "our", "Thesaurus.", "\n", "}", "\n", "\n", "MyThesaurus::thesaurus_data_type", "const", "&amp&quot;, "MyThesaurus::get_thesaurus_data()", "{", "\n", "static", "thesaurus_data_type", "thesaurus_data&quot;, "\n", "if", "(",
"thesaurus_data.empty()", ")", "{", "\n", "//", "\n", "//", "Construct", "thesaurus", "data", "\"by", "hand\"", "for", "this", "example.", "A", "real", "thesaurus", "would", "probably", "be", "read", "from", "disk.", "\n", "//", "Note", "that", "every", "list", "of", "synonyms", "must", "always", "include", "the", "original", "phrase.", "\n", "//", "\n", "static", "synonyms_type", "synonyms&quot;, "\n", "synonyms.push_back(", "\"foo\"", ")&quot;, "\n", "synonyms.push_back(", "\"foobar\"", ")&quot;, "\n", "thesaurus_data[", "\"foo\"", "]", "=", "&amp;synonyms&quot;, "\n", "thesaurus_data[", "\"foobar\"", "]", "=", "&amp;synonyms&quot;, "\n", "}", "\n", "return", "thesaurus_data&quot;, "\n", "}", "\n", "\n", "MyThesaurus::iterator::ptr", "MyThesaurus::lookup(", "String", "const", "&amp;phrase,", "String", "const", "&amp;relationship,", "\n", "range_type", "at_least,", "range_type", "at_most", ")", "const", "{", "\n", "static", "thesaurus_data_type", "const", "&amp;thesaurus_data", "=", "get_thesaurus_data()&quot;, "\n", "thesaurus_data_type::const_iterator", "const", "entry", "=", "thesaurus_data.find(", "phrase", ")&quot;, "\n", "iterator::ptr", "result&quot;, "\n", "if", "(", "entry", "!=", "thesaurus_data.end()", ")", "\n", "result.reset(", "new", "iterator(", "*entry-&gt;second", ")", ")&quot;, "\n", "return", "(", "result", ")&quot;, "std::move", "\n", "}", "\n", "\n", "void", "MyThesaurus::iterator::destroy()", "const", "{", "\n", "delete", "this", "&quot;, "\n", "}", "\n", "\n", "bool", "MyThesaurus::iterator::next(", "String", "*synonym", ")", "{", "\n", "if", "(", "i_", "!=", "synonyms_.end()", ")", "{", "\n", "*synonym", "=", "*i_&quot;, "//", "not", "*i_++", "since", "post-increment", "is", "less", "efficient", "\n", "++i_&quot;, "\n", "return", "true", "&quot;, "\n", "}", "\n", "return", "false", "&quot;, "\n", "}", "\n", "A real thesaurus would load a large number of synonyms, of course.", "\n", "\n", "The ThesaurusProvider Class", "\n", "The ",
"ThesaurusProvider", " class is:", "class", "ThesaurusProvider", ":", "public", "Resource", "{", "\n", "public", ":", "\n", "typedef", "/*", "implementation-defined", "*/", "ptr&quot;, "\n", "\n", "virtual", "bool", "getThesaurus(", "lang,", "Thesaurus::ptr", "*thesaurus", "=", "0", ")", "locale::iso639_1::type", "const", "=", "0&quot;, "\n", "void", "destroy()", "const", "&quot;, "//", "inherited", "from", "Resource", "\n", "}&quot;, "\n", "To implement a ", "ThesaurusProvider", ", you need to implement the ", "getThesaurus()", " function where:", "\n", "lang", "  ", "The desired language of the thesaurus.  ", "\n", "\n", "  ", "thesaurus", "If not ", ", set to point to a thesaurus for ", ".  ", "null", "lang", "\n", "\n", "The ", "getThesaurus()", " function returns ", "true", " only if it can provide a thesaurus for the given language. Continuing with the example, a very simple ", "ThesaurusProvider", " can be implemented as:", "class", "MyThesaurusProvider", ":", "pulic", "ThesaurusProvider", "{", "\n", "public", ":", "\n", "void", "destroy()", "const", "&quot;, "\n", "bool", "getThesaurus(", "iso639_1::type", "lang,", "Thesaurus::ptr*", "=", "0", ")", "const", "&quot;, "\n", "}&quot;, "\n", "\n", "void", "MyThesaurusProvider::destroy()", "const", "{", "\n", "//", "Do", "nothing", "since", "we", "statically", "allocate", "a", "singleton", "instance", "of", "our", "ThesaurusProvider.", "\n", "}", "\n", "\n", "bool", "MyThesaurusProvider::getThesaurus(", "lang,", "Thesaurus::ptr", "*result", ")", "iso639_1::type", "const", "{", "\n", "//", "\n", "//", "Since", "our", "tiny", "thesaurus", "contains", "only", "universally", "known", "words,", "we", "don't", "bother", "checking", "lang", "\n", "//", "and", "always", "return", "true.", "\n", "//", "\n", "static", "MyThesaurus", "thesaurus&quot;, "\n", "if", "(", "result", ")", "\n", "result-&gt;reset(", "&amp;thesaurus", ")&quot;, "\n", "return", "true", "&quot;, "\n", "}", "\n", "\n", "\n", "A Thesaurus URL Resolver
Class", "\n", "In addition to a ", "Thesaurus", " and ", "ThesaurusProvider", ", you must also implement a \"thesaurus resolver\" class that, given a URI, provides a ", "ThesaurusProvider", " for that URI. A simple ", "ThesaurusURLResolver", " for our simple thesaurus can be implemented as:", "class", "ThesaurusURLResolver", ":", "public", "URLResolver", "{", "\n", "public", ":", "\n", "ThesaurusURLResolver(", "String", "const", "&amp;url", ")", ":", "url_(", "url", ")", "{", "}", "\n", "Resource*", "resolveURL(", "String", "const", "&amp;url,", "EntityData", "const", "*", ")&quot;, "//", "inherited", "\n", "private", ":", "\n", "String", "const", "url_&quot;, "\n", "}&quot;, "\n", "\n", "Resource*", "ThesaurusURLResolver::resolveURL(", "String", "const", "&amp;url,", "EntityData", "const", "*data", ")", "const", "{", "\n", "if", "(", "data-&gt;getKind()", "==", "EntityData::THESAURUS", ")", "\n", "static", "MyThesaurusProvider", "provider&quot;, "\n", "if", "(", "uri", "==", "uri_", ")", "\n", "return", "&amp;provider&quot;, "\n", "}", "\n", "return", "0&quot;, "\n", "}", "\n", "For more on ", "URLResolver", ", see ", "URI Resolvers", ".", "\n", "\n", "Using Your Thesaurus", "\n", "To enable your thesaurus to be used, you need to add it to a static context:", "StaticContext_t", "sctx", "=", "zorba-&gt;createStaticContext()&quot;, "\n", "ThesaurusURLResolver", "resolver(", "\"http://www.example.com\"", ")&quot;, "\n", "sctx-&gt;registerURLResolver(", "&amp;resolver", ")&quot;, "\n", "You can then perform a query using your thesaurus:", "let", "$x", ":=", "&lt;msg&gt;foobar&lt;/msg&gt&quot;, "\n", "return", "$x", "contains", "text", "\"foo\"", "\n", "using", "thesaurus", "at", "\"http://www.example.com\"", "&quot;, "\n", " ", "\n" ] }, ())
