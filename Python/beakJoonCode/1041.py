import sys
input = sys.stdin.readline

number_of_dice_faces = int(input())
dice_faces_values = list(map(int, input().split()))

if number_of_dice_faces == 1:
    print(sum(dice_faces_values) - max(dice_faces_values))
else:
    minimal_opposite_faces = [
        min(dice_faces_values[0], dice_faces_values[5]),
        min(dice_faces_values[1], dice_faces_values[4]),
        min(dice_faces_values[2], dice_faces_values[3])
    ]
    minimal_opposite_faces.sort()
    
    two_faces_sum_on_edge = (minimal_opposite_faces[0] + minimal_opposite_faces[1]) * (number_of_dice_faces - 1) * 4
    two_faces_sum_on_edge_inner = (minimal_opposite_faces[0] + minimal_opposite_faces[1]) * (number_of_dice_faces - 2) * 4
    three_faces_sum_on_corner = (minimal_opposite_faces[0] + minimal_opposite_faces[1] + minimal_opposite_faces[2]) * 4
    one_face_sum_on_surface = minimal_opposite_faces[0] * (number_of_dice_faces - 2) * 4
    one_face_sum_on_inner = minimal_opposite_faces[0] * (number_of_dice_faces - 2) * (number_of_dice_faces - 2) * 5
    
    print(two_faces_sum_on_edge + two_faces_sum_on_edge_inner + three_faces_sum_on_corner + one_face_sum_on_surface + one_face_sum_on_inner)
