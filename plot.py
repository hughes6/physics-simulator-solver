import matplotlib.pyplot as plt
import numpy as np

# INPUTS ==============================
save = False
separate = False
combined = True
separate_and_combined = False
filename = "test.txt"
# INPUTS ==============================

data = []
with open(filename) as f: # t x y z vx vy vz ax ay az
  lines = f.readlines()
  # Skip header if present
  for line in lines:
    if line.startswith('t'):
      continue
    if line.strip():  # skip empty lines
      values = line.strip().split(',')
      data.append([float(v) for v in values])

data = np.array(data) # convert to arr

# Extract columns
t = data[:, 0]      # time
x = data[:, 1]      # x position
y = data[:, 2]      # y position
z = data[:, 3]      # z position
vx = data[:, 4]     # x velocity
vy = data[:, 5]     # y velocity
vz = data[:, 6]     # z velocity
ax = data[:, 7]     # x acceleration
ay = data[:, 8]     # y acceleration
az = data[:, 9]     # z acceleration

if separate_and_combined or separate:
  # Plot 1: X, Vx, Ax vs Time
  plt.figure(figsize=(10, 6))

  plt.subplot(3, 1, 1)
  plt.plot(t, x, 'b-', linewidth=2)
  plt.ylabel('X Position (m)')
  plt.title('X Direction: Position, Velocity, Acceleration vs Time')
  plt.grid(True, alpha=0.3)

  plt.subplot(3, 1, 2)
  plt.plot(t, vx, 'r-', linewidth=2)
  plt.ylabel('Vx Velocity (m/s)')
  plt.grid(True, alpha=0.3)

  plt.subplot(3, 1, 3)
  plt.plot(t, ax, 'g-', linewidth=2)
  plt.xlabel('Time (s)')
  plt.ylabel('Ax Acceleration (m/s²)')
  plt.grid(True, alpha=0.3)

  plt.tight_layout()
  if save:
    plt.savefig('x_vx_ax_vs_t.png', dpi=300, bbox_inches='tight')
  plt.show()

  # Plot 2: Y, Vy, Ay vs Time
  plt.figure(figsize=(10, 6))

  plt.subplot(3, 1, 1)
  plt.plot(t, y, 'b-', linewidth=2)
  plt.ylabel('Y Position (m)')
  plt.title('Y Direction: Position, Velocity, Acceleration vs Time')
  plt.grid(True, alpha=0.3)

  plt.subplot(3, 1, 2)
  plt.plot(t, vy, 'r-', linewidth=2)
  plt.ylabel('Vy Velocity (m/s)')
  plt.grid(True, alpha=0.3)

  plt.subplot(3, 1, 3)
  plt.plot(t, ay, 'g-', linewidth=2)
  plt.xlabel('Time (s)')
  plt.ylabel('Ay Acceleration (m/s²)')
  plt.grid(True, alpha=0.3)

  plt.tight_layout()
  if save:
    plt.savefig('y_vy_ay_vs_t.png', dpi=300, bbox_inches='tight')
  plt.show()

  # Plot 3: Z, Vz, Az vs Time
  plt.figure(figsize=(10, 6))

  plt.subplot(3, 1, 1)
  plt.plot(t, z, 'b-', linewidth=2)
  plt.ylabel('Z Position (m)')
  plt.title('Z Direction: Position, Velocity, Acceleration vs Time')
  plt.grid(True, alpha=0.3)

  plt.subplot(3, 1, 2)
  plt.plot(t, vz, 'r-', linewidth=2)
  plt.ylabel('Vz Velocity (m/s)')
  plt.grid(True, alpha=0.3)

  plt.subplot(3, 1, 3)
  plt.plot(t, az, 'g-', linewidth=2)
  plt.xlabel('Time (s)')
  plt.ylabel('Az Acceleration (m/s²)')
  plt.grid(True, alpha=0.3)

  plt.tight_layout()
  if save:
    plt.savefig('z_vz_az_vs_t.png', dpi=300, bbox_inches='tight')
  plt.show()




if separate_and_combined or combined:
  # If you want all three directions in one figure
  fig, axes = plt.subplots(3, 3, figsize=(10, 6))

  # X direction
  axes[0, 0].plot(t, x, 'b-', linewidth=2)
  axes[0, 0].set_ylabel('X (m)')
  axes[0, 0].set_title('Position X')
  axes[0, 0].grid(True, alpha=0.3)

  axes[1, 0].plot(t, vx, 'r-', linewidth=2)
  axes[1, 0].set_ylabel('Vx (m/s)')
  axes[1, 0].grid(True, alpha=0.3)

  axes[2, 0].plot(t, ax, 'g-', linewidth=2)
  axes[2, 0].set_ylabel('Ax (m/s²)')
  axes[2, 0].set_xlabel('Time (s)')
  axes[2, 0].grid(True, alpha=0.3)

  # Y direction
  axes[0, 1].plot(t, y, 'b-', linewidth=2)
  axes[0, 1].set_ylabel('Y (m)')
  axes[0, 1].set_title('Position Y')
  axes[0, 1].grid(True, alpha=0.3)

  axes[1, 1].plot(t, vy, 'r-', linewidth=2)
  axes[1, 1].set_ylabel('Vy (m/s)')
  axes[1, 1].grid(True, alpha=0.3)

  axes[2, 1].plot(t, ay, 'g-', linewidth=2)
  axes[2, 1].set_ylabel('Ay (m/s²)')
  axes[2, 1].set_xlabel('Time (s)')
  axes[2, 1].grid(True, alpha=0.3)

  # Z direction
  axes[0, 2].plot(t, z, 'b-', linewidth=2)
  axes[0, 2].set_ylabel('Z (m)')
  axes[0, 2].set_title('Position Z')
  axes[0, 2].grid(True, alpha=0.3)

  axes[1, 2].plot(t, vz, 'r-', linewidth=2)
  axes[1, 2].set_ylabel('Vz (m/s)')
  axes[1, 2].grid(True, alpha=0.3)

  axes[2, 2].plot(t, az, 'g-', linewidth=2)
  axes[2, 2].set_ylabel('Az (m/s²)')
  axes[2, 2].set_xlabel('Time (s)')
  axes[2, 2].grid(True, alpha=0.3)

  plt.suptitle('Motion in 3D: Position, Velocity, Acceleration vs Time', fontsize=16)
  plt.tight_layout()
  if save:
    plt.savefig('all_motion_plots.png', dpi=300, bbox_inches='tight')
  plt.show()