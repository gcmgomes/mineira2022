#!/usr/bin/env python
# encoding: utf-8
# Solucao do problema "Cipher"
# Fabiola Pereira (fabiola.pereira@ufu.br)
# Maratona Mineira de Programacao 2022

#Q . . . T . . . N . . . E . . . E . . . E . . . A . . . S 
#. U . M . E . O . H . C . N . O . S . U . C . J . M . I . 
#. . E . . . C . . . E . . . A . . . Q . . . E . . . A . . 



cypher = str(input())
n= int(input())

#cypher = "QTNEEEASUMEOHCNOSUCJMIECEAQEA"
#cypher = "PIAEJOUODQE"
#cypher = "QEEUHCUCENEQESMONSJITCAEAAEOM"
#cypher = "QETCNEEAEQEEAASUMEOHCNOSUCJMI"
#cypher = "QUEMTECONHECENAOESQUECEJAMAIS"

m = len(cypher)


if n == 1:
	print(cypher)

else:

	len_first_cycle = n

	number_full_cycles = ((m-n) // (n-1))
	len_last_cycle = ((m-n) % (n-1))

	if (((m-n) % (n-1)) == 0):
		number_full_cycles = number_full_cycles-1
		len_last_cycle = n-1


	finish_down = False
	finish_up = False
	if (number_full_cycles + 1) % 2 == 0:
		finish_down = True
	else:
		finish_up = True


	if number_full_cycles % 2 == 0:
		number_ups = number_full_cycles // 2
		number_downs = number_full_cycles // 2
	else:
		number_ups = (number_full_cycles // 2) + 1
		number_downs = number_full_cycles // 2

	number_downs = number_downs + 1



	#print('len_first_cycle', len_first_cycle)
	#print('len_last_cycle', len_last_cycle)
	#print('number_full_cycles', number_full_cycles)
	#print('number_downs', number_downs)
	#print('number_ups', number_ups)


	blocks_size = []
	for i in range(n):
		blocks_size.append(0)
	blocks_size[0] = number_ups + 1
	blocks_size[n-1] = number_downs

	if finish_down:
		if len_last_cycle == n-1:
			blocks_size[n-1] = blocks_size[n-1] + 1

	if finish_up:
		if len_last_cycle == n-1:
			blocks_size[0] = blocks_size[0] + 1


	number_of_parts = number_full_cycles + 2

	number_of_positions_receive_full = len_last_cycle
	if len_last_cycle == n-1:
		number_of_positions_receive_full = number_of_positions_receive_full-1


	#print('finish_down', finish_down)
	#print('finish_up', finish_up)
	#print('number_of_parts', number_of_parts)
	#print('number_of_positions_receive_full', number_of_positions_receive_full)


	if finish_down:
		for i in range(1, number_of_positions_receive_full+1):
			blocks_size[i] = number_of_parts
		for i in range(number_of_positions_receive_full+1, n-1):
			blocks_size[i] = number_of_parts-1



	if finish_up:
		for i in range(n-2, (n-2)-number_of_positions_receive_full, -1):
			blocks_size[i] = number_of_parts
		for i in range((n-2)-number_of_positions_receive_full, 0, -1):
			blocks_size[i] = number_of_parts-1


	#print(blocks_size)




	blocks = []
	for i in range(len(blocks_size)):
		blocks.append(0)
	total = 0
	for i in range(len(blocks_size)):
		init = total
		total = total + blocks_size[i]
		blocks[i] = cypher[init:total]

	#print(blocks)


	j_out = 0
	j_in = 0
	to_right = True
	to_left = False
	border_right = False
	border_left = False

	for k in range(0,len(blocks[0])):
		if to_right:
			for i in range(0,len(blocks)):
				#print('cima', i)
				if border_right:
					print(blocks[i][j_out], end='')
					border_right = False
					continue
				if (i == 0) or (i == len(blocks)-1):
					border = True	
				else:
					border = False
				if border:
					if j_out < len(blocks[i]):
						print(blocks[i][j_out], end='')
						border = False
				else:
					if j_in < len(blocks[i]):
						print(blocks[i][j_in], end='')
			to_right = False
			to_left = True
			j_in = j_in + 1
			border_right = False
			border_left = True


		if to_left:
			for i in range(len(blocks)-1, 0, -1):
				#print('aqui', i)
				if border_left:
					border_left = False
					continue
				if (i == 0) or (i == len(blocks)-1):
					border = True	
				else:
					border = False
				if border:
					if j_out < len(blocks[i]):
						print(blocks[i][j_out], end='')
						border = False
				else:
					if j_in < len(blocks[i]):
						print(blocks[i][j_in], end='')
			to_right = True
			to_left = False
			j_in = j_in + 1
			border_right = True
			border_left = False
			
		j_out = j_out + 1

	print()




