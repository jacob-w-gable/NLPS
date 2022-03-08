# NLPS Native Interpreter
* NLPS allows for users to easily and quickly create a personal assistant with minimal to no programming experience. 
* It allows conversational interactions with the computer to be very natural. 
* It is not hardware intensive. 
* It allows user/computer interaction that requires context. 
* The author has the ability to execute tasks and store global variables.

## Documentation Table of Contents
### [Basic NLPS Syntax](#basic-nlps-syntax-1)
* [Hello World](#hello-world)
* [Dialog Statements](#dialog-statements)
  * [Person](#person)
  * [Computer](#computer)
  * [Responses and Dialog Blocks](#responses-and-dialog-blocks)
* [How Dialog Blocks are Processed](#how-dialog-blocks-are-processed)
* [Using Brackets Instead of Indentions](#using-brackets-instead-of-indentions)
* [Comments](#comments)
* [Synonyms](#synonyms)
  * [Defining Synonyms](#defining-synonyms)
  * [Placement of Synonyms](#placement-of-synonyms)
  * [Deleting Synonyms](#deleting-synonyms)
* [Example Program](#example-program)
### [Intermediate NLPS Syntax](#intermediate-nlps-syntax-1)
* [Dialog Blocks Beginning with Computer](#dialog-blocks-beginning-with-computer)
  * [When Time is](#when-time-is)
  * [When Starting Program](#when-starting-program)
  * [When Stopping Program](#when-stopping-program)
  * [Logical When](#logical-when)
* [Contractions](#contractions)
* [Making Statements Natural](#making-statements-natural)
  * [Polystatements](#polystatements)
  * [Grouping](#grouping)
  * [Optional Words](#optional-words)
* [Escape Keys](#escape-keys)
* [Importing NLPH Files](#importing-nlph-files)
* [Functional Dialog Part 1](#functional-dialog-part-1)
  * [Concept](#concept)
  * [From NLPS File](#from-nlps-file)
  * [From NLPH File](#from-nlph-file)
* [Mixing Brackets and Indentions](#mixing-brackets-and-indentions)
* [Example Program](#example-program-1)
### [Advanced NLPS Syntax](#advanced-nlps-syntax-1)
* [Changing the Default Response](#changing-the-default-response)
* [Modifying or Disabling Contractions](#modifying-or-disabling-contractions)
* [Running Terminal/Shell Command From A Statement](#running-terminalshell-command-from-a-statement)
* [Determining Which Computer Statement to Follow](#determining-which-computer-statement-to-follow)
  * [With ID's](#with-ids)
  * [With Indices](#with-indices)
* [Storing Variables](#storing-variables)
* [Weighted Chance Polystatements, Grouping, and Optional Words](#weighted-chance-polystatements-grouping-and-optional-words)
* [Functional Dialog Part 2](#functional-dialog-part-2)
* [Example Program](#example-program-2)
### [Compiling](#compiling-1)
* [Windows](#windows)
* [Linux](#linux)
### [Cumulative Example](#cumulative-example-1)

	
# Documentation
## Basic NLPS Syntax
Programs are written in NLPS (Natural Language Processing Script) files. The file names end in `.nlps`. For example, `filename.nlps`. This section will describe to you the syntax needed to create basic programs using NLPS. 
### Hello World
Here is a simple hello world program that makes the computer respond "Hello, person!" when the person says "Hello, computer!":

	person: Hello, computer!
		computer: Hello, person!

### Dialog Statements
**Dialog statements** are the sentences and phrases that will be said by either the computer or the user when using the application. There are two types: `person` and `computer`.
#### Person
A line in the script that is stated by the human is given by `person:`:

	person: Remind me to do the dishes.
	
#### Computer
A line in the script that is stated by the computer is given by `computer:`:

	computer: It is now time to do the dishes.
	
#### Responses and Dialog Blocks
In order to make a conversation flow, the user and computer have the ability to respond to one another. A **response** is represented in the script as an indention in the spacing followed by the `person` or `computer` keywords. Indentions can be made with either tabs or spaces, but the spacing must be consistent throughout the entire file for the code to work. Here is an example of a conversation where the computer makes a response to the user:
	
	person: Hello, computer!
		computer: Oh, hello there!
		
Here is an example where the user responds to the computer:
	
	computer: How has your day been?
		person: My day has been good.
		
In more complex conversations, the heirarchy tree could be much deeper and have many different outcomes. Consider the following example, where the computer wants details about when to set the alarm, and the user could have multiple responses:
	
	computer: What time should I wake you up tomorrow?
		person: Wake me up at 7:00 AM.
			computer: Ok, I will wake you up at 7:00 AM.
		person: Wake me up at 7:00 PM.
			computer: Ok, I will wake you up at 7:00 PM.
		person: Wake me up at 7:00.
			computer: Is that AM or PM?
				person: AM
					computer: Ok, I will wake you up at 7:00 AM.
				person: PM
					computer: Ok, I will wake you up at 7:00 PM.
		person: I don't want to be woken up tomorrow.
			computer: Ok, I won't wake you up tomorrow.

These conversation trees are called **dialog blocks**. You will likely want to put many dialog blocks into a single `.nlps` file. To do this, all you have to do is start a new line and make sure the indentions are correct. If the indentions are wrong, the script will be processed incorrectly. Here is an example with two independent dialog blocks in the same file:

	person: Hello, computer!
		computer: Oh, hello there!
		
	person: Good morning!
		computer: Good morning, friend!
		
### How Dialog Blocks are Processed
Take the following script as an example:
	
	person: Hello, computer!
		computer: Oh, hello there!
		
	person: Good morning!
		computer: Good morning, friend!
	
	person: What's your name?
		computer: My name is Computer.
		
	person: Wake me up tomorrow morning.
		computer: At 6:00 AM or 7:00 AM?
			person: At 6:00 AM.
				computer: Ok, I will wake you up at 6:00 AM.
			person: At 7:00 AM.
				computer: Ok, I will wake you up at 7:00 AM.
		
When the user makes a statement to the computer, it iterates through the root of each dialog block to see if it finds a match. If it finds a match, it will respond accordingly. For example... 
* if the user says, "What's your name?" the computer will respond, "My name is Computer." 
* if the user says, "How old are you?" the computer will not make a meaningful response, because the programmer did not specify a response for that. 
* if the user says, "At 6:00 AM." the computer will not make a meaningful response, because that dialog statement is not a root of any dialog block.
* if the user says, "Wake me up tomorrow morning." the computer will respond, "At 6:00 AM or 7:00 AM?". After that, it looks for an answer from the user...
  * If the user says, "What's your name?" the computer will not make a meaningful response, because the programmer did not specify a response for that at this level of the dialog block.
  * If the user says, "At 6:00 AM." the computer will respond, "Ok, I will wake you up at 6:00 AM."

### Using Brackets Instead of Indentions
For some people, using indentions to organize the code is impractical or more difficult. It is also possible to organize code using brackets, but it must be specified that you are doing so in the code, and statements must end with semicolons if they have no responses under them. The specification to use brackets is given by the keyword `#brackets#`. Take the following code as an example:

	person: Hello, computer!
		computer: Oh, hello there!
		
	person: Good morning!
		computer: Good morning, friend!
	
	person: What's your name?
		computer: My name is Computer.
		
	person: Wake me up tomorrow morning.
		computer: At 6:00 AM or 7:00 AM?
			person: At 6:00 AM.
				computer: Ok, I will wake you up at 6:00 AM.
			person: At 7:00 AM.
				computer: Ok, I will wake you up at 7:00 AM.
				
To write this code with brackets instead of indentions, it must be written like so:
	
	#brackets#
	
	person: Hello, computer! {
		computer: Oh, hello there!;
	}
	
	person: Good morning! {
		computer: Good morning, friend!;
	}
	
	person: What's your name? {
		computer: My name is Computer.;
	}
	
	person: Wake me up tomorrow monring. {
		computer: At 6:00 AM or 7:00 AM? {
			person: At 6:00 AM. {
				computer: Ok, I will wake you up at 6:00 AM.;
			}
			person: At 7:00 AM. {
				computer: Ok, I will wake you up at 7:00 AM.;
			}
		}
	}
	
Note that spacing does not matter when you are using brackets. The previous code would also be valid if it was written in a less organized fashion, such as:

	#brackets#
	
	person: Hello, computer! {computer: Oh, hello there!;}
	
	person: Good morning! {
	computer: Good morning, friend!;
	}
	
	person: What's your name? {
		computer: My name is Computer.;
	}
	
	person: Wake me up tomorrow monring. {
		computer: At 6:00 AM or 7:00 AM? {
			person: At 6:00 AM. {
				computer: Ok, I will wake you up at 6:00 AM.;
			}
			person: At 7:00 AM. {
				computer: Ok, I will wake you up at 7:00 AM.;
			}}}
	
### Comments
It is useful to write notes in the code that are not read by the computer. To write a note, write a double-slash (`//`) followed by your desired notes:

	// write your comments here
	
The double-slash makes the entire rest of the line a comment, but not the text before the double-slash. So, you can put comments at the end of a line of code:

	person: Hello, computer! // the person is able to say this to the computer, but this sentence will not be part of the code.

If you want a comment to be on multiple lines, use slash-star (`/*`) to start the comment, and star-slash (`*/`) to end the comment:
	
	/* multi-
	   line
	   comment */
	   
### Synonyms
Synonyms allow your programs to be more flexible. If you define a set of synonyms, your scripts don't need to be quite as explicit. For example, if "hi" and "hello" are synonyms, then the sentence "Hi, computer!" would be valid for the statement:

	person: Hello, computer!

#### Defining Synonyms
To define synonym sets, use the `synonyms` keyword. The keyword is followed by lines that contain synonym sets. Each set is simply a list of each word, seperated by a slash.

	synonyms
		close/near
		far / distant
		close by / near here
		small/tiny/petit
		
Note that the spacing between the words in question doesn't matter, only the slash. You may also have more than two synonyms per definition.

#### Placement of Synonyms
Synonym definitions should be placed at the beginning of the file. Otherwise, they will not apply to the dialogs that come before the synonym definitions. The following example is **correct**:

	synonyms
		french fries / chips
		
	person: remind me to buy french fries
		computer: Ok, I will remind you.
		
However, this example is **incorrect**:
	
	person: remind me to buy french fries
		computer: Ok, I will remind you.
		
	synonyms
		french fries / chips
		
There may be certain situations where you don't want synonyms to be defined before a certain dialog block, but you **do** want it to be defined after the dialog block. In those situations, the previous example may actually be correct. However, as a general rule, you will usually want to define the synonyms at the beginning of the file so that it applies to all dialog blocks.	

#### Deleting Synonyms
To delete synonym relations, use the `delete synonyms` line followed by the synonym relations that must be deleted:

	delete synonyms
		close/near
		far/distant
		small/tiny
		
This deletes the synonym relations of these six words from this point forward in the code. Referencing the [Defining Synonyms](#defining-synonyms) example above, notice how the relations `small/petit` and `tiny/petit` still exist. <br>
In order to delete all synonym or antonym relations for the upcoming code, use the `purge` syntax:
	
	purge synonyms

### Example Program
## Intermediate NLPS Syntax
This section will tell you how to initiate dialog blocks that begin with the computer. Later, it equip you with the necessary syntax to make conversations with the computer feel more natural. There are five ways of making the conversations feel natural: synonyms, contractions, polystatements, grouping, and optional words. Synonyms has already been discussed, but this section will discuss the remaining four. 
### Dialog Blocks Beginning with Computer
If a dialog block that begins with computer is expected to run at any point, the author must specify a trigger to start the dialog. To do this, use a `when` clause before the dialog statement.
#### When Time Is
The most basic usage of the `when` keyword is to start a dialog statement at a certain time. The syntax for doing so is `when time is <h:mm> [AM/pm]`. Replace `<h:mm>` with the time that you want the dialog to run every day in the format `h:mm`. Putting `AM` or `PM` is optional if you use a 24-hour time format, but otherwise it will default to AM. Therefore, `AM` is always optional. 

	when time is 9:00 PM
	computer: What time should I wake you up tomorrow?
		person: Wake me up at 7:00 AM.
			computer: Ok, I will wake you up at 7:00 AM.
		person: Wake me up at 7:00 PM.
			computer: Ok, I will wake you up at 7:00 PM.
		person: Wake me up at 7:00.
			computer: Is that AM or PM?
				person: AM
					computer: Ok, I will wake you up at 7:00 AM.
				person: PM
					computer: Ok, I will wake you up at 7:00 PM.
		person: I don't want to be woken up tomorrow.
			computer: Ok, I won't wake you up tomorrow.

`time is` is not the only time-related keyword. Here is a full list of all valid keywords related to time:

	when time is <h:mm> [AM/pm]
	when day is <monday/tuesday/wednesday/thurday/friday/saturday/sunday/m/t/w/th/f/st/sn>
	when date is <1-31>
	when month is <1-12/january/february/march/april/may/june/july/august/september/october/november/december/jan/feb/mar/apr/may/jun/jul/aug/sep/oct/nov/dec>
	when year is <2000-9999>
	
#### When Starting Program
It is also useful to initiate a dialog statement when a particular program starts on the computer. The syntax to do this is `when starting <path-to-program>`.

	when starting "C:\Program Files\JetBrains\IntelliJ IDEA Community Edition 2020.3\bin\idea64.exe"
	
Note that if the path has spaces in it, quotation marks are required.
#### When Stopping Program
To initiate a dialog when a program stops, use `when stopping <path-to-program>`.

	when stopping "C:\Program Files\JetBrains\Intellij IDEA Community Edition 2020.3\bin\idea64.exe"
	
#### Logical When
There are many cases where you need several `when` statements in one. These statements can be strung together using `and` or `or`, and they can be negated using `not`. For example, you may not need an alarm on the weekends...

	when time is 9:00 pm and day is not friday and day is not saturday
	computer: What time should I wake you up tomorrow?
		person: Wake me up at 7:00 AM.
			computer: Ok, I will wake you up at 7:00 AM.
		person: Wake me up at 7:00 PM.
			computer: Ok, I will wake you up at 7:00 PM.
		person: Wake me up at 7:00.
			computer: Is that AM or PM?
				person: AM
					computer: Ok, I will wake you up at 7:00 AM.
				person: PM
					computer: Ok, I will wake you up at 7:00 PM.
		person: I don't want to be woken up tomorrow.
			computer: Ok, I won't wake you up tomorrow.
			
Logical grouping can be achieved with parenthesis (`()`). Another way to write the `when` clause is using or's and parenthesis instead of and's and not's:

	when time is 9:00 pm and ( day is sunday or day is monday or day is tuesday or day is wednesday or day is thursday )

However, this is a bit much to type. For `time`, `day`, `date`, `month`, `year`, `starting`, and `stopping` statements, you can also use lists. For example, the clause in parenthesis above could be written as:

	day is sunday monday tuesday wedesday thursday
	
This statement is equivalent to stringing together a bunch of `or` statements and eliminates the need for parenthesis. So the following is valid:

	when time is 9:00 pm and day is sunday monday tuesday wednesday thursday

The following is also valid
	
	when time is 9:00 pm and day is not friday saturday
	
### Contractions
Contractions are the second way of making statements natural. However, the script author does not need to worry about contractions, as they are automatically processed in a way similar to synonyms. The list is based on common American English. As a usage example, consider the statement:

	person: What are you doing?
	
If the person were to instead ask the phrase, "What're you doing?" the branch would still execute, because "What're" is equivalent to "What are".
<br>
Here is a full list of contractions:
	
	are not / aren't
	cannot / can't
	could have / could've
	could not / couldn't
	did not / didn't
	does not / doesn't
	do not / don't
	is / 's
	had not / hadn't
	has not / hasn't
	have not / haven't
	he had / he'd
	he would / he'd
	he shall / he'll
	he will / he'll
	how will / how'll
	how does / how's
	I would / I'd
	I shall / I'll
	I will / I'll
	I am / I'm
	I have / I've
	is not / isn't
	it would / it'd
	it shall / it'll
	it will / it'll
	let us / let's
	might have / might've
	must not / mustn't
	must have / must've
	she had / she'd
	she would / she'd
	she shall / she'll
	she will / she'll
	should have / should've
	should not / shouldn't
	that shall / that'll
	that will / that'll
	that are / that're
	that would / that'd
	there would / there'd
	there shall / there'll
	there will / there'll
	they would / they'd
	they shall / they'll
	they will / they'll
	they are / they're
	they have / they've
	was not / wasn't
	we would / we'd
	we shall / we'll
	we will / we'll
	we are / we're
	we have / we've
	were not / weren't
	what did / what'd
	what shall / what'll
	what will / what'll
	what are / what're
	what does / what's
	what have / what've
	where did / where'd
	where shall / where'll
	where will / where'll
	where does / where's
	where shall / where'll
	where will / where'll
	where does / where's
	where have / where've
	which would / which'd
	which shall / which'll
	which will / which'll
	who would / who'd
	who shall / who'll
	who will / who'll
	who are / who're
	why did / why'd
	why are / why're
	why does / why's
	will not / won't
	would have / would've
	would not / wouldn't
	you had / you'd
	you would / you'd
	you shall / you'll
	you will / you'll
	you are / you're
	you have / you've
	you all / y'all
	
### Making Statements Natural
In order for the computer to interpret the user in a natural way, statements should not follow a strict, explicit script. The user will have some variation in the way they say things to the computer. Additionally, in order for the computer to feel natural and alive, the computer should not say the exact same phrase to the user every time it goes through a specific conversation. There are three ways for a script author to achieve this: either-or statements, grouping, and optional words.
#### Polystatements
If a statement could be said one of two ways, a user could seperate these possibilities by a slash (`/`):
	
	person: Wake me up tomorrow morning. / Set an alarm for tomorrow morning.

It is also possible for the statement to be said in more than two ways:
	
	person: Wake me up tomorrow morning. / Set an alarm for tomorrow morning. / Get me up tomorrow morning.
	
#### Grouping
Sometimes, all possible ways a statement could be said could have similarities. For example, consider the statement:

	person: Wake me up tomorrow morning. / Set an alarm for tomorrow morning. / Get me up tomorrow morning.
	
There are three ways the statement could be said. However, they each end in `tomorrow morning`. The only variation is in the first few words. So, we could group the first part of the sentence together using brackets (`[]`) and putting the slashes inside the brackets to represent the variation.

	person: [Wake me up / Set an alarm for / Get me up] tomorrow morning.
	
It is also possible for grouping to be nested. Notice how two of the possible options in the brackets end with the same thing ("Wake *me up*" and "Get *me up*"). The above statement could be further simplified:
	
	person: [[Wake/Get] me up / Set an alarm for] tomorrow morning. 
	
#### Optional Words
Some words do not need to exist at all, even though they could. In order to make words optional, use parentheses (`()`). For example, the statement used above (in the Grouping section) could be simplified to:

	person: [[Wake/Get] me up / Set an alarm for] tomorrow (morning).


### Escape Keys
// TODO: elaborate <br>
If you require brackets, parentheses, or slashes to be part of the statement, then they must be escaped.

	\(
	\)
	\[
	\]
	\/
	\\
	\$
	
### Importing NLPH Files
It is usually helpful for synonym definitions to be isolated among files, because synonyms for one task probably won't be suitable for a different task. For this reason, synonms do not apply cross-file. However, if it is necessary that they do apply cross-file, you can put those synonyms into a  `.nlph` (Natural Language Processing Header) file. Then you can import that file to the top of a `.nlps` file. `.nlph` files can be imported into a `.nlps` file using the `use "my-program.nlph"` syntax. Example:<br>

*my-synonyms.nlph* 
	
	synonyms:
		hi/hello
		
*hello-world.nlps*

	use "my-synonyms.nlps"
	
	person: Hello, computer!
		computer: Oh, hello there!
		
The contents of *my-synonyms.nlps* is copied-and-pasted to the top of *hello-world.nlps*. This way, if you require the same synonyms for multiple files, you don't have to write them twice.<br>
`.nlph` files can also be imported into other `.nlph` files.

### Functional Dialog Part 1
#### Concept
Consider the following two hypthetical dialog blocks:

	person: wake me up at eight oclock
		computer: am or pm?
			person: am
			person: pm
			
	person: remind me to do the dishes at eight oclock
		computer: am or pm?
			person: am
			person: pm
	
Each dialog block ends in the same thing, yet you have to write it twice. To get around this, you can use functional dialogs. By assigning an ID to a dialog block, you can initiate it from the middle of another dialog block. To give a dialog an ID, write a name after the `person` or `computer` tag. For example, let's create a dialog that gets whether the user wants AM or PM that has the ID `AmOrPm`:

	computer AmOrPm: am or pm?
		person: am
		person: pm
		
In order to use this functional dialog, call it by putting double-parenthesis (`()`) after the ID in the middle of some dialog blocks:
	
	person: wake me up at eight oclock
		AmOrPm()
		
	person: remind me to do the dishes at eight oclock
		AmOrPm()
	
#### From NLPS File
Consider the following functional dialog, which may be accessed from the middle of some other dialog blocks:
	
	person SetTime: the time is 9:00
		computer: am or pm?
			person: am
			person: pm

If this block is called from the middle of some other dialog block, it would be initiated. Additionally, if the user were to simply tell the computer "the time is 9:00", the dialog block would be initiated then as well. If you don't want this block to be called when the user says "the time is 9:00" (meaning, you ONLY want it to be able to be called from the middle of some other dialog block), precede the `person` keyword with `ignored`:

	ignored person SetTime: the time is 9:00
		computer: am or pm?
			person: am
			person: pm

#### From NLPH File
It is very useful to put functional dialogs inside `.nlph` files. Since `.nlph` files can be imported into more than one other document, all dialog blocks in `.nlph` files are ignored by default. If you need a dialog block in a `.nlph` file to be processed (which is not recommended), you can use the `recognized` keyword:

	recognized person SetTime: the time is 9:00
		computer: am or pm?
			person: am
			person: pm

### Mixing Brackets and Indentions
The usage of brackets and the usage of indetions have both already been discussed, however it is also possible to use both styles in a single document. If the keyword `#brackets#` is used, all of the code that follows must follow bracketed formatting. However, it is notable that the usage of this keyword does not change the requirements of the code that precedes it. Therefore, you can switch back and forth between bracketed and indentive formatting thoughout a document. To switch back to indentive formatting, use the `#indentions#` keyword. All of the code that comes after that line must follow indented formatting. 

	person: Hello, computer!
		computer: Oh, hello there!
		
	#brackets#
		
	person: Good morning! {
		computer: Good morning, friend!;
	}
	
	person: What's your name? {
		computer: My name is Computer.;
	}
		
	#indentions#
	
	person: Wake me up tomorrow morning.
		computer: At 6:00 AM or 7:00 AM?
			person: At 6:00 AM.
				computer: Ok, I will wake you up at 6:00 AM.
			person: At 7:00 AM.
				computer: Ok, I will wake you up at 7:00 AM.

### Example Program
Consider the following statement:
	
	person: [[Wake/Get] me up / Set an alarm for] tomorrow (morning).

This statement uses each of the three methods to make statements natural. Therefore, the computer will expand this statement into 6 different statements:
	
	Wake me up tomorrow.
	Wake me up tomorrow morning.
	Get me up tomorrow.
	Get me up tomorrow morning.
	Set an alarm for tomorrow.
	Set an alarm for tomorrow morning.
	
If the user says any of these six statements, the conversation will be allowed to continue on the branch. Otherwise, it will not be recognized.
	
## Advanced NLPS Syntax
### Changing the Default Response
Sometimes the user will say a phrase that does not match any `person` statement in a dialog. By defualt, the computer will respond, "I do not understand that." If you want to change it to something else use `default-response: <response-phrase>`. Example:

	default-response: Your statement confuses me.
	
This default response applies to everything that comes after the statement. It can be changed multiple times throughout a document. 
### Modifying or Disabling Contractions
Technically, contractions are synonyms; they function exactly the same. If you don't want or need certain contraction pairs or you want to add some, the syntax to modify contractions is the same as it is for [synonyms](#synonyms), except that it uses the `contractions` keyword instead of `synonyms`. 
	
	delete contractions
		he would / he'd
		
	contractions
		he would / he'd
		
The only difference is that contractions are binary, whereas synonyms can have more than two words on a single line.
### Running Terminal/Shell Command From A Statement
You can run a CLI commands when a statement is executed by putting the commands at the end of a statement. Here are some exaples of what you might see on Windows:

	person: open my internet browser -> open_browser.bat
	
	person: lock my front door -> lock_door.exe
	
Here is what it may look like on Linux:
	
	person: open my internet browser -> ./open_browser.sh
	
	person: lock my front door -> ./lock_door
	
Of course, these can also be run after computer statements.

	computer: it is time to wake up -> start_alarm.exe
	
### Determining Which Computer Statement to Follow
Consider the following dialog:
	
	person: what day is it?
		computer: monday
		computer: tuesday
		computer: wednesday
		computer: thursday
		computer: friday
		computer: saturday
		computer: sunday
		
How would the computer know how to respond? The response could be seven different things. The solution to determining which response to make is to run an external program that returns the answer by printing to the console. This can be done with indices or with ID's. 
#### With Indices
To do this with indices, you must simply return the index number of the response that you want by printing it from the program run from the person statement. Let's create a python program that gets the day of the week in numeric form (0 for Monday, 1 for Tuesday, ... 6 for Sunday). <br>
*DayOfWeek.py*:
	
	import datetime

	print(datetime.datetime.today().weekday())
	
The dialog statement would then look as follows:
	
	person: what day is it -> python3 DayOfWeek.py
		computer: monday
		computer: tuesday
		computer: wednesday
		computer: thursday
		computer: friday
		computer: saturday
		computer: sunday
		
#### With ID's
The example in the last section is more practically done by using indices, but we will use the same scenario to show how ID's work. To use ID's, you must assign an ID to each response in the dialog block. In this example, we use the ID's `mon`, `tue`, `wed`, `thu`, `fri`, `sat`, `sun`.
	
	person: what day is it -> python3 DayOfWeek.py
		computer mon: monday
		computer tue: tuesday
		computer wed: wednesday
		computer thu: thursday
		computer fri: friday
		computer sat: saturday
		computer sun: sunday
		
*DayOfWeek.py* would have to be modified to return one of the ID's instead of a number:

	import datetime

	day = datetime.datetime.today().weekday()

	dayindices = {
	    0: "mon",
	    1: "tue",
	    2: "wed",
	    3: "thu",
	    4: "fri",
	    5: "sat",
	    6: "sun"
	}

	print(dayindices.get(day))
	
### Storing Variables
Variables can be saved from person statements and read again from computer statements. Variables can have whatever name you want, but they must have a dollar sign (`$`) on the front. Here is a dialog block that assigns the computer a name:
	
	person: your name is $name
		computer: Ok, from now on you can call me $name

The `$name` variable is saved on the computer's hard drive and accessed again in the computer statement. It can be saved or read again at any time from anywhere. 

### Weighted Chance Polystatements, Grouping, and Optional Words
### Functional Dialog Part 2
### Example Program
## Compiling
### Windows
Compile with flag `-std=gnu++17`
### Linux
Compile with flag `-std=c++17`
## Cumulative Example

// TODO: scopes<br>
// TODO: verbal programming<br>
// TODO: check intervals to start computer dialog
