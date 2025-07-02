import subprocess
import base64

def generate_payload(payload_type, command):
    result = subprocess.run(
        ['./whysoserial-cpp', payload_type, command],
        capture_output=True, text=True
    )
    # Parse the output to get the Base64
    lines = result.stdout.split('\n')
    for i, line in enumerate(lines):
        if line.strip() == "Base64:":
            return lines[i+1].strip()
    return None

# Usage example
payload = generate_payload("object1", "whoami")
