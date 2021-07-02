#include <stdio.h>
#include <string.h>
#include <stdint.h>
#define i32 int32_t

i32 main()
{
	printf("Please enter the JSON string:");
	char Jstr[2049] = {'\0'};
	fgets(Jstr, 2049, stdin);
	Jstr[strlen(Jstr) - 1] = '\0';

	// {
	//     "firstName":"John",
	//     "lastName":"Smith",
	//     "sex":"male","age": 25,
	//     "address":
	//     {
	//         "streetAddress":"212ndStreet",
	//         "city":"NewYork","state":"NY",
	//         "postalCode":"10021"
	//     },
	//     "phoneNumber":
	//     [
	//         {
	//             "type":"home","number":"212555-1234"
	//         },
	//         {
	//             "type":"fax","number":"646555-4567"
	//         }
	//     ]
	// }
	i32 exit = 0;
	while (!exit)
	{
		i32 choice = 0;
		printf("Choice (0:Exit,1:Get) : ");

		scanf("%d", &choice);

		if (choice == 1)
		{
			char key[100] = {'\0'};
			printf("Key: ");
			fgets(key, 100, stdin);
			fgets(key, 100, stdin);
			key[strlen(key) - 1] = '\0';
		}
		else if (choice == 0)
		{
			exit = 1;
		}
		else
		{
			printf("invalid input, please try again\n");
		}
	}
	printf("Bye\n");

	return 0;
}
