
version: "2.3"
services:
  emby:
    image: emby/embyserver
    container_name: embyserver
    runtime: nvidia # Expose NVIDIA GPUs
    network_mode: host # Enable DLNA and Wake-on-Lan
    environment:
      - UID=1000 # The UID to run emby as (default: 2)
      - GID=100 # The GID to run emby as (default 2)
      - GIDLIST=100 # A comma-separated list of additional GIDs to run emby as (default: 2)
    volumes:
      - /docker/emby:/config # Configuration directory
      - /media/home/NAS/Serien:/mnt/share1 # Media directory
      - /media/home/NAS/Filme:/mnt/share2 # Media directory
    ports:
      - 8096:8096 # HTTP port
      - 8920:8920 # HTTPS port
    devices:
      - /dev/dri:/dev/dri # VAAPI/NVDEC/NVENC render nodes
      - /dev/vchiq:/dev/vchiq # MMAL/OMX on Raspberry Pi
    restart: on-failure